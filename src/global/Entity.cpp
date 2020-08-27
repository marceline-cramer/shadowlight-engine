#include "global/Entity.hpp"

Entity::~Entity()
{
    for(auto c : components) {
        delete c;
    }
    components.clear();
}

void Entity::finalize()
{
    for(auto c : components) {
        c->finalize(components);
    }
}

void Entity::addComponent(Component* c)
{
    components.insert(c);
}
