#pragma once

#include "components/Component.hpp"

#include "config/TransformConfig.hpp"

class TransformComponent : public Component
{
public:
    COMPONENT_TYPE("Transform");

    TransformComponent() { transform = {.position=glm::vec3(0.0),.orientation=glm::quat()}; }
    TransformComponent(TransformConfig&);
    virtual ~TransformComponent() {};

    virtual void update(EntityTransform, double) {};
    virtual void finalize(ComponentSet&) {};
    virtual void createBindings(lua_State*) {};

    virtual void getTransform(EntityTransform* _transform) { *_transform = transform; };
protected:
    EntityTransform transform;
};
