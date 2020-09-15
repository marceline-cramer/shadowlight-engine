#pragma once

#include <vulkan/vulkan.h>

#include "components/Component.hpp"

class RendererComponent : public Component
{
public:
    virtual void render(VkCommandBuffer) = 0;
private:
};
