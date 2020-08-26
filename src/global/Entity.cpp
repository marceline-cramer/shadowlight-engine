#include "global/Entity.hpp"

#include "components/ScriptComponent.hpp"

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
        auto scriptComponent = dynamic_cast<ScriptComponent*>(c);
        if(scriptComponent) {
            scriptComponent->finalize(components);
        }
    }
}

void Entity::addComponent(Component* c)
{
    components.insert(c);
}
