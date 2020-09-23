#include "components/FirstPersonControllerComponent.hpp"

FirstPersonControllerComponent::FirstPersonControllerComponent(InputAxis* _ax, InputAxis* _ay)
{
    ax = _ax;
    ay = _ay;

    tilt = M_PI/2.0;
    pan = -M_PI/2.0;
}

void FirstPersonControllerComponent::update()
{
    pan += ax->getAxis();
    tilt += ay->getAxis();

    if(tilt <= 0.0) tilt = 0.0;
    if(tilt >= M_PI) tilt = M_PI;

    glm::quat newOrientation =
        glm::angleAxis((float)M_PI-tilt, glm::vec3(-1.0, 0.0, 0.0)) *
        glm::angleAxis(pan, glm::vec3(0.0, 0.0, 1.0));

    transform->orientation = newOrientation;
    transform->position = glm::vec3(0.0, 0.0, 1.0);
}

void FirstPersonControllerComponent::finalize(ComponentSet&, EntityTransform& _transform)
{
    transform = &_transform;
}
