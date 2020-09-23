#include "global/Entity.hpp"

Entity::Entity()
{
    transform.position = glm::vec3(0.0);
    transform.orientation = glm::quat();
}

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
        c->finalize(components, transform);
    }
}

void Entity::addComponent(Component* c)
{
    components.insert(c);
}
