#include "bindings/vk/RenderAttachment.hpp"

RenderAttachment::RenderAttachment(VulkanInstance* _vki, uint32_t width, uint32_t height, VkImageUsageFlags usage, VkImageAspectFlags aspectFlags, VkFormat _format)
{
    vki = _vki;
    imageFormat = _format;

    vki->createImage(width, height, imageFormat, VK_IMAGE_TILING_OPTIMAL, usage, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, image, imageMemory);
    vki->createImageView(image, imageFormat, aspectFlags, imageView);
}

RenderAttachment::~RenderAttachment()
{
    vkDestroyImageView(vki->device, imageView, nullptr);
    vkDestroyImage(vki->device, image, nullptr);
    vkFreeMemory(vki->device, imageMemory, nullptr);
}
