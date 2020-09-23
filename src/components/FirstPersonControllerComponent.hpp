#pragma once

#include "components/Component.hpp"

#include "input/InputAxis.hpp"

class FirstPersonControllerComponent : public Component
{
public:
    COMPONENT_TYPE("FirstPersonController");

    FirstPersonControllerComponent(InputAxis*, InputAxis*, InputAxis*, InputAxis*);

    virtual void update();
    virtual void finalize(ComponentSet&, EntityTransform&);
private:
    EntityTransform* transform;

    const float cameraSpeed = 0.001;

    float pan;
    float tilt;

    InputAxis* panAxis;
    InputAxis* tiltAxis;
    InputAxis* truckAxis;
    InputAxis* dollyAxis;
};
