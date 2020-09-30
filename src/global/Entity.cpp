#include "global/Entity.hpp"

Entity::Entity(EntityTransform _transform)
{
    transformComponent = nullptr;
}

Entity::~Entity()
{
    for(auto c : components) {
        delete c;
    }
    components.clear();
}

void Entity::update(double dt)
{
    EntityTransform transform;

    if(transformComponent) {
        transformComponent->getTransform(&transform);
    } else {
        transform = {
            .position = glm::vec3(0.0, 0.0, 0.0),
            .orientation = glm::quat()
        };
    }

    for(auto c : components) {
        c->update(transform, dt);
    }
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

    auto newTransform = dynamic_cast<TransformComponent*>(c);
    if(newTransform) {
        if(transformComponent) {
            throw std::runtime_error("Entity already has TransformComponent");
        }

        transformComponent = newTransform;
    }
}
