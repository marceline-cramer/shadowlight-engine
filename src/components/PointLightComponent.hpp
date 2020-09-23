#pragma once

#include <set>

#include "components/RendererComponent.hpp"

class PointLightComponent;
using PointLightSet = std::set<PointLightComponent*>;

class PointLightComponent : public RendererComponent
{
public:
    COMPONENT_TYPE("PointLight");

    PointLightComponent(PointLightSet*);
    ~PointLightComponent();

    virtual void update(double);
    virtual void finalize(ComponentSet&, EntityTransform&);
    virtual void render(VkCommandBuffer, CameraComponent*);
private:
    PointLightSet* parentSet;
    EntityTransform* transform;
};
