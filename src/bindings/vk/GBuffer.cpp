#include "bindings/vk/GBuffer.hpp"

GBuffer::GBuffer(VkPhysicalDevice physicalDevice, VkDevice device, uint32_t width, uint32_t height)
{
    auto depthFormat = findSupportedFormat(
        physicalDevice,
        {VK_FORMAT_D32_SFLOAT,
        VK_FORMAT_D32_SFLOAT_S8_UINT,
        VK_FORMAT_D24_UNORM_S8_UINT},
        VK_IMAGE_TILING_OPTIMAL,
        VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
    );

    depthAttachment     = new RenderAttachment(physicalDevice, device, width, height, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_IMAGE_ASPECT_DEPTH_BIT, depthFormat);
    radianceAttachment  = new RenderAttachment(physicalDevice, device, width, height, VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VK_IMAGE_ASPECT_COLOR_BIT, VK_FORMAT_R32G32B32A32_SFLOAT);
    albedoAttachment    = new RenderAttachment(physicalDevice, device, width, height, VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VK_IMAGE_ASPECT_COLOR_BIT, VK_FORMAT_R8G8B8A8_UNORM);
    positionAttachment  = new RenderAttachment(physicalDevice, device, width, height, VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VK_IMAGE_ASPECT_COLOR_BIT, VK_FORMAT_R32G32B32A32_SFLOAT);
    normalAttachment    = new RenderAttachment(physicalDevice, device, width, height, VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VK_IMAGE_ASPECT_COLOR_BIT, VK_FORMAT_R32G32B32A32_SFLOAT);
    propertyAttachment  = new RenderAttachment(physicalDevice, device, width, height, VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VK_IMAGE_ASPECT_COLOR_BIT, VK_FORMAT_R8G8B8A8_UNORM);

    deferredAttachments = {
        albedoAttachment,
        positionAttachment,
        normalAttachment,
        propertyAttachment
    };
}

GBuffer::~GBuffer()
{
    delete depthAttachment;
    delete radianceAttachment;
    delete albedoAttachment;
    delete positionAttachment;
    delete normalAttachment;
    delete propertyAttachment;
}

VkFormat GBuffer::findSupportedFormat(VkPhysicalDevice physicalDevice, const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features)
{
    for(VkFormat format : candidates) {
        VkFormatProperties props;
        vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &props);

        if(tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
            return format;
        } else if(tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
            return format;
        }
    }

    throw std::runtime_error("Failed to find supported format");
}
