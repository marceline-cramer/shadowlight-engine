#pragma once

#include <vulkan/vulkan.h>

class Pipeline
{
public:
    virtual ~Pipeline() {};

    virtual void render(VkCommandBuffer) = 0;
private:
};
