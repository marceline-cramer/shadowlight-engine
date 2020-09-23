#include "components/PointLightComponent.hpp"

PointLightComponent::PointLightComponent(PointLightSet* _parentSet)
{
    parentSet = _parentSet;

    parentSet->insert(this);
}

PointLightComponent::~PointLightComponent()
{
    parentSet->erase(this);
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
