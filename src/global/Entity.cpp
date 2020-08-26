#include "global/Entity.hpp"

void Entity::addComponent(Component* c)
{
    components.insert(c);
}
