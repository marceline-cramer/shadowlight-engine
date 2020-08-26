#include "global/Scene.hpp"

#include "components/ScriptComponent.hpp"

Scene::Scene(Filesystem* _fs)
{
    fs = _fs;

    // Load the config.json file
    rapidjson::Document config;
    fs->loadJson("config.json", config);
}

Scene::~Scene()
{
    
}

void Scene::load(LuaBinding* lua)
{
    /*auto entity = new Entity();

    auto componentScript = new ScriptComponent();
    entity->addComponent(componentScript);
    componentScript->init(lua, entity->components);

    addEntity(entity);*/
}

void Scene::update()
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
            c->update();
        }
    }
}

void Scene::addEntity(Entity* e)
{
    entities.insert(e);
}
