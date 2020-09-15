#pragma once

#include "bindings/VulkanBinding.hpp"

#include "pipelines/Pipeline.hpp"

class MeshPipeline : public Pipeline
{
public:
    MeshPipeline(VulkanBinding*);

    void render(VkCommandBuffer);
private:
    VulkanBinding* vk;
};
