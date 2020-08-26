#pragma once

#include <string>
#include <set>
#include <map>

#include "components/Component.hpp"

class Entity;
using EntitySet = std::set<Entity*>;

class Entity
{
public:
    void addComponent(Component*);
//private:
    Entity* parent;
    EntitySet children;

    ComponentSet components;
};
