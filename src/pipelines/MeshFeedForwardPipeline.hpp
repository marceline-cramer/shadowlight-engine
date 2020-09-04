#pragma once

#include "bindings/VulkanBinding.hpp"

#include "global/Filesystem.hpp"

#include "pipelines/Pipeline.hpp"

class MeshFeedForwardPipeline : public Pipeline
{
public:
    MeshFeedForwardPipeline(VulkanBinding*, Filesystem*);
    ~MeshFeedForwardPipeline();
private:
    // Vulkan objects
    VkPipelineLayout pipelineLayout;

    // Bindings
    VulkanBinding* vk;
    Filesystem* fs;
};
