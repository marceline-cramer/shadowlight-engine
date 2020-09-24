#pragma once

#include <stdexcept>
#include <vector>

#include "shaderc/shaderc.hpp"

#include "bindings/VulkanBinding.hpp"

#include "pipelines/Pipeline.hpp"

class CompositePipeline : public Pipeline
{
public:
    CompositePipeline(VulkanBinding*);
    ~CompositePipeline();
    
    virtual void render(VkCommandBuffer, CameraComponent*);
private:
    void createSetLayout();
    void createPipelineLayout();
    void createPipeline();
    void createDescriptorPool();
    void createDescriptorSet();
    void writeDescriptorSet();
    VkShaderModule compileShader(const char*, std::string, shaderc_shader_kind);

    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    VkDescriptorPool descriptorPool;
    VkDescriptorSet descriptorSet;
};
