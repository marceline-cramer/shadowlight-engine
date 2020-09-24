#pragma once

#include <vector>

#include "shaderc/shaderc.hpp"

#include "bindings/VulkanBinding.hpp"

#include "pipelines/Pipeline.hpp"

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
    VkShaderModule compileShader(const char*, std::string, shaderc_shader_kind);

    GBuffer gBuffer;
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    VkDescriptorPool descriptorPool;
    VkDescriptorSet descriptorSet;
};
