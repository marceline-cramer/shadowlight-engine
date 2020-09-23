#pragma once

#include "components/Component.hpp"

class FirstPersonControllerComponent : public Component
{
public:
    COMPONENT_TYPE("FirstPersonController");

    FirstPersonControllerComponent();

    virtual void update();
    virtual void finalize(ComponentSet&, EntityTransform&);
private:
    EntityTransform* transform;

    float pan;
    float tilt;
};
