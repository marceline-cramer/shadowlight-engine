#pragma once

#include "components/Component.hpp"

#include "config/TransformConfig.hpp"

class TransformComponent : public Component
{
public:
    TransformComponent() { transform = {.position=glm::vec3(0.0),.orientation=glm::quat()}; }
    TransformComponent(TransformConfig&);
    virtual ~TransformComponent() {};

    virtual void getTransform(EntityTransform* _transform) { *_transform = transform; };
protected:
    EntityTransform transform;
};
