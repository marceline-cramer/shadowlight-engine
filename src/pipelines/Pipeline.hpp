#pragma once

#include <vulkan/vulkan.h>

class Pipeline
{
public:
    virtual ~Pipeline() {};

    virtual void render(VkCommandBuffer, VkFramebuffer) = 0;
private:
};
