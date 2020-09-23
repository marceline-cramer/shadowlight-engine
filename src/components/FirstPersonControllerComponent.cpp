#include "components/FirstPersonControllerComponent.hpp"

FirstPersonControllerComponent::FirstPersonControllerComponent()
{
    tilt = M_PI/2.0;
    pan = -M_PI/2.0;
}

void FirstPersonControllerComponent::update()
{
    auto rotation = glm::vec3(0.0, -tilt, pan);
    auto newOrientation = glm::quat(rotation);
    transform->orientation = newOrientation;
    transform->position = glm::vec3(2.0, 0.0, 0.5);
}

void FirstPersonControllerComponent::finalize(ComponentSet&, EntityTransform& _transform)
{
    transform = &_transform;
}
