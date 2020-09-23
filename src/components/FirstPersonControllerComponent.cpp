#include "components/FirstPersonControllerComponent.hpp"

FirstPersonControllerComponent::FirstPersonControllerComponent(InputAxis* _panAxis, InputAxis* _tiltAxis, InputAxis* _truckAxis, InputAxis* _dollyAxis)
{
    panAxis = _panAxis;
    tiltAxis = _tiltAxis;
    truckAxis = _truckAxis;
    dollyAxis = _dollyAxis;

    tilt = M_PI/2.0;
    pan = -M_PI/2.0;
}

void FirstPersonControllerComponent::update(double dt)
{
    pan += panAxis->getAxis();
    tilt += tiltAxis->getAxis();

    if(tilt <= 0.0) tilt = 0.0;
    if(tilt >= M_PI) tilt = M_PI;

    glm::quat newOrientation =
        glm::angleAxis((float)M_PI-tilt, glm::vec3(-1.0, 0.0, 0.0)) *
        glm::angleAxis(pan, glm::vec3(0.0, 0.0, 1.0));

    transform->orientation = newOrientation;

    auto truckDirection = glm::vec3(glm::cos(pan), -glm::sin(pan), 0.0) * cameraSpeed;
    auto forwardDirection = glm::vec2(glm::sin(pan), glm::cos(pan));
    auto upDirection = glm::vec2(glm::sin(tilt), glm::cos(tilt));
    auto dollyDirection = glm::vec3(
        forwardDirection.x * upDirection.x,
        forwardDirection.y * upDirection.x,
        upDirection.y) * cameraSpeed;

    transform->position += truckDirection * truckAxis->getAxis();
    transform->position += dollyDirection * dollyAxis->getAxis();
}

void FirstPersonControllerComponent::finalize(ComponentSet&, EntityTransform& _transform)
{
    transform = &_transform;
}
