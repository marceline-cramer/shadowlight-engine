#include "global/Entity.hpp"

Entity::Entity(EntityTransform _transform)
{
    transform = _transform;

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
    if(transformComponent) {
        transformComponent->getTransform(&transform);
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
        transformComponent->setTransform(transform);
    }
}
