#pragma once

#include <vector>

#include "bindings/vk/RenderAttachment.hpp"

class GBuffer
{
public:
    GBuffer(VkPhysicalDevice, VkDevice, uint32_t, uint32_t);
    ~GBuffer();

    std::vector<RenderAttachment*> getDeferredAttachments() { return deferredAttachments; }
//private:
    VkFormat findSupportedFormat(VkPhysicalDevice, const std::vector<VkFormat>&, VkImageTiling, VkFormatFeatureFlags);

    RenderAttachment* depthAttachment;
    RenderAttachment* radianceAttachment;
    RenderAttachment* albedoAttachment;
    RenderAttachment* positionAttachment;
    RenderAttachment* normalAttachment;
    RenderAttachment* propertyAttachment;

    std::vector<RenderAttachment*> deferredAttachments;
};
