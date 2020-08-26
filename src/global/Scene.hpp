#pragma once

#include <set>

#include "global/Entity.hpp"
#include "global/Filesystem.hpp"

#include "bindings/LuaBinding.hpp"

#include "assets/AssetPool.hpp"
#include "assets/ScriptAsset.hpp"

using BucketMap = std::map<std::string, ComponentSet>;

class Scene
{
public:
    Scene(LuaBinding*, Filesystem*);
    ~Scene();
    
    void load();
    void loadEntity(rapidjson::Value&);
    void loadComponent(Entity*, rapidjson::Value&);
    void update();
    void addEntity(Entity*);
private:
    // Scene state
    std::set<Entity*> entities;
    std::string currentScene;
    bool reloadFlag = false;

    // Asset pools
    AssetPool<ScriptAsset>* scriptPool;

    // Bindings
    LuaBinding* lua;
    Filesystem* fs;
};
