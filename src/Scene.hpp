#pragma once

#include <set>

#include "Entity.hpp"

#include "bindings/LuaBinding.hpp"

using BucketMap = std::map<std::string, ComponentSet>;

class Scene
{
public:
    Scene();
    ~Scene();
    
    void load(LuaBinding*);
    void update();
    void addEntity(Entity*);
private:
    std::set<Entity*> entities;
};
