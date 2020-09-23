#pragma once

#include <vulkan/vulkan.h>

#include "components/Component.hpp"
#include "components/CameraComponent.hpp"

class RendererComponent : public Component
{
public:
    virtual void render(VkCommandBuffer, CameraComponent*) = 0;
private:
};
