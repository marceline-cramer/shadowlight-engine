#pragma once

#include <set>

#include <vulkan/vulkan.h>

#include "components/RendererComponent.hpp"

class Pipeline
{
public:
    virtual ~Pipeline() {};

    virtual void render(VkCommandBuffer) = 0;

    std::set<RendererComponent*> rendererComponents;

    class VulkanBinding* vk;
private:
};
