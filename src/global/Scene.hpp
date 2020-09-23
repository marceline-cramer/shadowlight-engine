#pragma once

#include <set>

#include "global/Entity.hpp"
#include "global/Filesystem.hpp"
#include "global/Window.hpp"

#include "bindings/LuaBinding.hpp"
#include "bindings/BulletBinding.hpp"
#include "bindings/OpenALBinding.hpp"

#include "assets/AssetPool.hpp"
#include "assets/ScriptAsset.hpp"

#include "components/ScriptComponent.hpp"
#include "components/SceneComponent.hpp"
#include "components/RigidBodyComponent.hpp"
#include "components/AudioSourceComponent.hpp"
#include "components/MeshRendererComponent.hpp"
#include "components/CameraComponent.hpp"
#include "components/FirstPersonControllerComponent.hpp"

#include "pipelines/MeshPipeline.hpp"

using BucketMap = std::map<std::string, ComponentSet>;

class Scene
{
public:
    Scene(Window*, VulkanBinding*, OpenALBinding*, BulletBinding*, LuaBinding*, Filesystem*);
    ~Scene();
    
    void load();
    void loadEntity(rapidjson::Value&);
    void loadComponent(Entity*, rapidjson::Value&);
    void loadScene(const char*);

    const char* getComponentString(rapidjson::Value&, const char*, const char*);

    void update(double);
    void addEntity(Entity*);

    bool shouldQuit() { return quitFlag; };
private:
    // Scene state
    std::set<Entity*> entities;
    std::string currentScene;
    bool reloadFlag = false;
    bool quitFlag = false;

    // Asset pools
    AssetPool<ScriptAsset>* scriptPool;
    AssetPool<AudioAsset>* audioPool;

    // Bindings
    Window* window;
    VulkanBinding* vk;
    OpenALBinding* oal;
    BulletBinding* bullet;
    LuaBinding* lua;
    Filesystem* fs;

    // Graphics pipelines
    MeshPipeline* meshPipeline;
};
