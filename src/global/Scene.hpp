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
    Scene(Filesystem*);
    ~Scene();
    
    void load(LuaBinding*);
    void update();
    void addEntity(Entity*);
private:
    std::set<Entity*> entities;

    // Asset pools
    AssetPool<ScriptAsset> scriptPool;

    // Bindings
    Filesystem* fs;
};
