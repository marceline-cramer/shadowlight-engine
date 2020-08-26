#include "global/Entity.hpp"

Entity::~Entity()
{
    for(auto c : components) {
        delete c;
    }
    components.clear();
}

void Entity::addComponent(Component* c)
{
    components.insert(c);
}
