#include "pipelines/CompositePipeline.hpp"

CompositePipeline::CompositePipeline(VulkanBinding* _vk)
{
    vk = _vk;
}

void CompositePipeline::render(VkCommandBuffer, CameraComponent*)
{

}
