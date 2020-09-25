#pragma once

#include <vector>

#include "bindings/VulkanBinding.hpp"

#include "components/PointLightComponent.hpp"

#include "shaders/PointLightShader.hpp"

#include "pipelines/Pipeline.hpp"

class PointLightPipeline : public Pipeline
{
public:
    PointLightPipeline(VulkanBinding*);
    ~PointLightPipeline();

    virtual void render(VkCommandBuffer, CameraComponent*);

    PointLightComponent* createPointLight();
private:
    void createInputSetLayout();
    void createUBOSetLayout();
    void createPipelineLayout();
    void createPipeline();
    void createDescriptorPool();
    void createInputSet();
    void writeInputSet();

    VulkanBinding* vk;

    GBuffer gBuffer;
    VkDescriptorSetLayout inputSetLayout;
    VkDescriptorSetLayout uboSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    VkDescriptorPool descriptorPool;
    VkDescriptorSet inputSet;

    PointLightSet pointLights;
};
