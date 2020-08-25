#pragma once

#include <string>
#include <set>
#include <map>

#include "Component.hpp"

class Entity;
using EntitySet = std::set<Entity*>;

class Entity
{
public:
    void update();
    void addComponent(Component*);
//private:
    Entity* parent;
    EntitySet children;

    ComponentMap components;
};
