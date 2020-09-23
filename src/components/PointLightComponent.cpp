#include "components/PointLightComponent.hpp"

PointLightComponent::PointLightComponent()
{

}

void PointLightComponent::update(double)
{

}

void PointLightComponent::finalize(ComponentSet&, EntityTransform& _transform)
{
    transform = &_transform;
}

void PointLightComponent::render(VkCommandBuffer, CameraComponent*)
{
    // TODO Shadow mapping
}
