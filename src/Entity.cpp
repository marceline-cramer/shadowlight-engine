#include "Entity.hpp"

void Entity::update()
{
    for(auto it : components) {
        it.second->update();
    }
}

void Entity::addComponent(Component* c)
{
    auto pair = std::pair<std::string, Component*>(c->getComponentType(), c);
    components.insert(pair);
}
