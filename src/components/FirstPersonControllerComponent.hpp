#pragma once

#include "components/Component.hpp"

#include "input/InputAxis.hpp"

class FirstPersonControllerComponent : public Component
{
public:
    COMPONENT_TYPE("FirstPersonController");

    FirstPersonControllerComponent(InputAxis*, InputAxis*);

    virtual void update();
    virtual void finalize(ComponentSet&, EntityTransform&);
private:
    EntityTransform* transform;

    float pan;
    float tilt;

    InputAxis* ax;
    InputAxis* ay;
};
