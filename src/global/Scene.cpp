#include "global/Scene.hpp"

Scene::Scene(EngineConfig* _engineConfig, Window* _window, VulkanBinding* _vk, OpenALBinding* _oal, BulletBinding* _bullet, LuaBinding* _lua, Filesystem* _fs)
{
    engineConfig = _engineConfig;
    window = _window;
    vk = _vk;
    oal = _oal;
    bullet = _bullet;
    lua = _lua;
    fs = _fs;

    // Create asset pools
    scriptPool = new AssetPool<ScriptAsset>(lua);
    audioPool = new AssetPool<AudioAsset>(oal);

    // Create pipelines
    deferredPipelines.insert(meshPipeline = new MeshPipeline(vk));

    lightingPipelines.insert(environmentMapPipeline = new EnvironmentMapPipeline(vk));
    lightingPipelines.insert(ambientLightPipeline = new AmbientLightPipeline(vk));
    lightingPipelines.insert(pointLightPipeline = new PointLightPipeline(vk));

    compositePipeline = new CompositePipeline(vk);

    // Load the first scene
    currentScene = engineConfig->firstScene;
    reloadFlag = true;
}

Scene::~Scene()
{
    // Delete entities
    for(auto e : entities) {
        delete e;
    }
    entities.clear();

    // Delete graphics pipelines
    delete meshPipeline;
    delete ambientLightPipeline;
    delete compositePipeline;
    delete pointLightPipeline;

    // Delete asset pools
    delete scriptPool;
    delete audioPool;
}

void Scene::load()
{
    if(currentScene == "exit") {
        quitFlag = true;
        return;
    }

    rapidjson::Document scene;
    fs->loadJson(currentScene.c_str(), scene);

    // Load skybox
    if(scene.HasMember("skybox")) {
        if(!scene["skybox"].IsString()) {
            throw std::runtime_error("scene.skybox must be a string");
        }

        environmentMapPipeline->setSkybox(scene["skybox"].GetString());
    } else {
        environmentMapPipeline->clearSkybox();
    }

    // Create entities
    if(scene.HasMember("entities")) {
        if(!scene["entities"].IsArray()) {
            throw std::runtime_error("scene.entities must be an array");
        }

        auto entities = scene["entities"].GetArray();
        for(auto e = entities.Begin(); e != entities.End(); e++) {
            // Create new entity
            if(e->IsObject()) {
                loadEntity(*e);
            } else if(e->IsString()) {
                rapidjson::Document entity;
                fs->loadJson(e->GetString(), entity);
                loadEntity(entity);
            } else {
                throw std::runtime_error("scene.entities.* must be a string or an object");
            }
        }
    }

    reloadFlag = false;
}

void Scene::loadEntity(rapidjson::Value& entity)
{
    Entity* e;

    if(entity.HasMember("name")) {
        if(!entity["name"].IsString()) {
            throw std::runtime_error("entity.name must be a string");
        }

        std::string name = entity["name"].GetString();
        std::cout << "Processing entity " << name << std::endl;
    }

    e = new Entity;
    entities.insert(e);

    if(entity.HasMember("components")) {
        if(!entity["components"].IsArray()) {
            throw std::runtime_error("entity.components must be an array");
        }

        auto components = entity["components"].GetArray();
        for(auto c = components.Begin(); c != components.End(); c++) {
            if(c->IsObject()) {
                loadComponent(e, *c);
            } else {
                throw std::runtime_error("entity.components.* must be an object");
            }
        }
    }

    e->finalize();
}

void Scene::loadComponent(Entity* e, rapidjson::Value& component)
{
    std::string componentType = getComponentString(component, componentType.data(), "type");
    std::cout << "Processing component of type " << componentType << std::endl;

    // Handle ScriptComponent
    if(componentType == ScriptComponent::ComponentType) {
        const char* scriptName = getComponentString(component, componentType.data(), "script");

        AssetHandle<ScriptAsset> script;
        scriptPool->load(scriptName, script);

        auto c = new ScriptComponent(script);
        e->addComponent(c);
    }
    // Handle SceneComponent
    else if(componentType == SceneComponent::ComponentType) {
        auto c = new SceneComponent(this);
        e->addComponent(c);
    }
    // Handle RigidBodyComponent
    else if(componentType == RigidBodyComponent::ComponentType) {
        auto c = new RigidBodyComponent(bullet, component);
        e->addComponent(c);
    }
    // Handle AudioSourceComponent
    else if(componentType == AudioSourceComponent::ComponentType) {
        const char* audioName = getComponentString(component, componentType.data(), "audio");

        AssetHandle<AudioAsset> audioAsset;
        audioPool->load(audioName, audioAsset);

        auto c = new AudioSourceComponent(audioAsset);
        e->addComponent(c);
    }
    // Handle MeshRendererComponent
    else if(componentType == MeshRendererComponent::ComponentType) {
        const char* meshName = getComponentString(component, componentType.data(), "mesh");
        const char* materialName = getComponentString(component, componentType.data(), "material");

        std::map<std::string, const char*> textures;

        if(component.HasMember("textures")) {
            if(!component["textures"].IsObject()) {
                throw std::runtime_error("component(MeshRenderer).textures must be an object");
            }

            auto textureMap = component["textures"].GetObject();
            for(auto t = textureMap.MemberBegin(); t != textureMap.MemberEnd(); t++) {
                if(!t->name.IsString()) {
                    throw std::runtime_error("component(MeshRenderer).textures key must be a string");
                }

                if(!t->value.IsString()) {
                    throw std::runtime_error("component(MeshRenderer).textures value must be a string");
                }

                textures.emplace(t->name.GetString(), t->value.GetString());
            }
        }

        auto c = meshPipeline->createMeshRenderer(meshName, materialName, textures);
        e->addComponent(c);
    }
    // Handle CameraComponent
    else if(componentType == CameraComponent::ComponentType) {
        const char* cameraTarget = getComponentString(component, componentType.data(), "target");

        auto c = vk->createCamera(cameraTarget);
        e->addComponent(c);
    }
    // Handle FirstPersonControllerComponent
    else if(componentType == FirstPersonControllerComponent::ComponentType) {
        // TODO Input config JSON
        auto c = new FirstPersonControllerComponent(
            window->getMouseX(), window->getMouseY(),
            window->createKeyboardAxis(SDL_SCANCODE_A, SDL_SCANCODE_D),
            window->createKeyboardAxis(SDL_SCANCODE_S, SDL_SCANCODE_W));
        e->addComponent(c);
    }
    // Handle PointLightComponent
    else if(componentType == PointLightComponent::ComponentType) {
        ConfigData configData{
            .root = component.GetObject(),
            .name = componentType
        };

        PointLightConfig config(configData);
        auto c = pointLightPipeline->createPointLight(config);
        e->addComponent(c);
    } else {
        throw std::runtime_error("Unrecognized component type " + componentType);
    }
}

void Scene::loadScene(const char* sceneName)
{
    currentScene = sceneName;
    reloadFlag = true;
}

const char* Scene::getComponentString(rapidjson::Value& component, const char* componentType, const char* stringName)
{
    if(!component.HasMember(stringName)) {
        std::ostringstream errorMessage;
        errorMessage << "component(" << componentType << ") must have " << stringName;
        throw std::runtime_error(errorMessage.str());
    }

    if(!component[stringName].IsString()) {
        std::ostringstream errorMessage;
        errorMessage << "component(" << componentType << ")." << stringName << " must be a string";
        throw std::runtime_error(errorMessage.str());
    }

    return component[stringName].GetString();
}

void Scene::update(double dt)
{
    // Create "buckets" for each component
    BucketMap buckets;

    // Register all components in the scene
    for(auto e : entities) {
        // Store each component by bucket
        for(auto c : e->components) {
            // Get the bucket corresponding to the component type
            BucketMap::iterator bucket = buckets.find(c->getComponentType());

            // If this component type has no bucket, create one
            if(bucket == buckets.end()) {
                auto newBucket = BucketMap::value_type(c->getComponentType(), ComponentSet());
                bucket = buckets.emplace(newBucket).first;
            }

            // Add this component to the appropriate bucket
            bucket->second.insert(c);
        }
    }

    // TODO Sort buckets by priority

    // Update all components
    for(auto bucket : buckets) {
        for(auto c : bucket.second) {
            c->update(dt);
        }
    }

    // Draw scene
    vk->render(deferredPipelines, lightingPipelines, compositePipeline, overlayPipelines);

    if(reloadFlag) {
        load();
    }
}

void Scene::addEntity(Entity* e)
{
    entities.insert(e);
}
