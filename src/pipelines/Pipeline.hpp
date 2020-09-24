#pragma once

#include <set>

#include <vulkan/vulkan.h>

#include "components/RendererComponent.hpp"
#include "components/CameraComponent.hpp"

class Pipeline;
using PipelineSet = std::set<Pipeline*>;

class Pipeline
{
public:
    virtual ~Pipeline() {};

    virtual void render(VkCommandBuffer, CameraComponent*) = 0;

    std::set<RendererComponent*> rendererComponents;

    class VulkanBinding* vk;
private:
};
