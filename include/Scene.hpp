#pragma once

#include <set>

#include "Entity.hpp"
#include "LuaBinding.hpp"

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