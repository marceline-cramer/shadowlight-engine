#pragma once

#include <set>

#include "Entity.hpp"

class Scene
{
public:
    void load();
    void update();
private:
    std::set<Entity*> entities;
};
