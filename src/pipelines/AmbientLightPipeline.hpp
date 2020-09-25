#pragma once

#include <vector>

#include "bindings/VulkanBinding.hpp"

#include "pipelines/Pipeline.hpp"

#include "shaders/AmbientLightShader.hpp"

class AmbientLightPipeline : public Pipeline
{
public:
    AmbientLightPipeline(VulkanBinding*);
    ~AmbientLightPipeline();
    
    virtual void render(VkCommandBuffer, CameraComponent*);
private:
    void createSetLayout();
    void createPipelineLayout();
    void createPipeline();
    void createDescriptorPool();
    void createDescriptorSet();
    void writeDescriptorSet();

    GBuffer gBuffer;
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    VkDescriptorPool descriptorPool;
    VkDescriptorSet descriptorSet;
};
