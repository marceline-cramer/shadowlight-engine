#pragma once

#include "components/TransformComponent.hpp"

#include "input/InputAxis.hpp"

class FirstPersonControllerComponent : public TransformComponent
{
public:
    COMPONENT_TYPE("FirstPersonController");

    FirstPersonControllerComponent(InputAxis*, InputAxis*, InputAxis*, InputAxis*);

    virtual void update(EntityTransform, double);
    virtual void finalize(ComponentSet&) {};
    virtual void createBindings(lua_State*) {};
    virtual void setTransform(EntityTransform _transform) { transform = _transform; }
    virtual void getTransform(EntityTransform* _transform) { *_transform = transform; }
private:
    EntityTransform transform;

    const float cameraSpeed = 10.0;

    float pan;
    float tilt;

    InputAxis* panAxis;
    InputAxis* tiltAxis;
    InputAxis* truckAxis;
    InputAxis* dollyAxis;
};
