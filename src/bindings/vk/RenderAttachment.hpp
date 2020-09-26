#pragma once

#include <stdexcept>

#include <vulkan/vulkan.h>

class RenderAttachment
{
public:
    RenderAttachment(VkPhysicalDevice, VkDevice, uint32_t, uint32_t, VkImageUsageFlags, VkImageAspectFlags, VkFormat);
    ~RenderAttachment();

    VkImageView getImageView() { return imageView; }
    VkFormat getFormat() { return imageFormat; }
private:
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    VkPhysicalDevice physicalDevice;
    VkDevice device;
    VkImage image;
    VkFormat imageFormat;
    VkDeviceMemory imageMemory;
    VkImageView imageView;
};
