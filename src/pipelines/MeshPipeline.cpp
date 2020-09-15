#include "pipelines/MeshPipeline.hpp"

MeshPipeline::MeshPipeline(VulkanBinding* _vk)
{
    vk = _vk;
}

void MeshPipeline::render(VkCommandBuffer commandBuffer)
{
    for(auto c : rendererComponents) {
        c->render(commandBuffer);
    }
}
