#pragma once

#include "components/PointLightComponent.hpp"

#include "pipelines/Pipeline.hpp"

class PointLightPipeline : public Pipeline
{
public:
    PointLightPipeline(VulkanBinding*);

    virtual void render(VkCommandBuffer, CameraComponent*);

    PointLightComponent* createPointLight();
private:
    VulkanBinding* vk;

    PointLightSet pointLights;
};
