#pragma once

#include <stdexcept>
#include <vector>

#include "bindings/VulkanBinding.hpp"

#include "pipelines/Pipeline.hpp"

#include "global/ShaderModule.hpp"

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

    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    VkDescriptorPool descriptorPool;
    VkDescriptorSet descriptorSet;
};
