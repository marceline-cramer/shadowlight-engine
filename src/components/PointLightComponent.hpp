#pragma once

#include "components/RendererComponent.hpp"

class PointLightComponent : public RendererComponent
{
public:
    COMPONENT_TYPE("PointLight");

    PointLightComponent();

    virtual void update(double);
    virtual void finalize(ComponentSet&, EntityTransform&);
    virtual void render(VkCommandBuffer, CameraComponent*);
private:
    EntityTransform* transform;
};
