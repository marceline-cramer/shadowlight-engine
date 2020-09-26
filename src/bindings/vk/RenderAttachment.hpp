#pragma once

#include <stdexcept>

#include <vulkan/vulkan.h>

#include "bindings/vk/VulkanInstance.hpp"

class RenderAttachment
{
public:
    RenderAttachment(VulkanInstance*, uint32_t, uint32_t, VkImageUsageFlags, VkImageAspectFlags, VkFormat);
    ~RenderAttachment();

    VkImageView getImageView() { return imageView; }
    VkFormat getFormat() { return imageFormat; }
private:
    VulkanInstance* vki;
    VkImage image;
    VkFormat imageFormat;
    VkDeviceMemory imageMemory;
    VkImageView imageView;
};
