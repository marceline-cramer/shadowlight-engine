#include "Entity.hpp"

void Entity::update()
{
    for(auto it : components) {
        it.first->update();
    }
}

void Entity::addComponent(Component* c)
{
    auto pair = ComponentMap::value_type(c, c->getComponentType());
    components.insert(pair);
}
