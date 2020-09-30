#pragma once

#include <string>
#include <set>
#include <map>

#include "components/Component.hpp"
#include "components/TransformComponent.hpp"

class Entity;
using EntitySet = std::set<Entity*>;

class Entity
{
public:
    Entity(EntityTransform);
    ~Entity();

    void update(double);
    
    void finalize();
    void addComponent(Component*);
//private:
    Entity* parent;
    EntitySet children;

    ComponentSet components;
    TransformComponent* transformComponent;
};
