#include "pipelines/PointLightPipeline.hpp"

PointLightPipeline::PointLightPipeline(VulkanBinding* _vk)
{
    vk = _vk;
}

void PointLightPipeline::render(VkCommandBuffer, CameraComponent*)
{

}

PointLightComponent* PointLightPipeline::createPointLight()
{
    auto pointLight = new PointLightComponent(&pointLights);
    return pointLight;
}
