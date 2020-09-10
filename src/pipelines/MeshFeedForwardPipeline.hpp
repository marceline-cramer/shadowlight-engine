#pragma once

#include "bindings/VulkanBinding.hpp"

#include "global/Filesystem.hpp"

#include "pipelines/Pipeline.hpp"

class MeshFeedForwardPipeline : public Pipeline
{
public:
    MeshFeedForwardPipeline(VulkanBinding*, Filesystem*);
    ~MeshFeedForwardPipeline();

    void draw(VkCommandBuffer);
private:
    // Vulkan objects
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;

    // Bindings
    VulkanBinding* vk;
    Filesystem* fs;
};
