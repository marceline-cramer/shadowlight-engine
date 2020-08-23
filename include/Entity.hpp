#pragma once

#include <string>
#include <set>
#include <map>

#include "Component.hpp"

class Entity
{
public:
    void update();
    void addComponent(Component*);
private:
    Entity* parent;
    std::set<Entity*> children;

    std::map<std::string, Component*> components;
};
