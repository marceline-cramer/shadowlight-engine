#pragma once

#include <vector>

#include "bindings/vk/VulkanInstance.hpp"
#include "bindings/vk/RenderAttachment.hpp"

class GBuffer
{
public:
    GBuffer(VulkanInstance*, uint32_t, uint32_t);
    ~GBuffer();

    std::vector<RenderAttachment*> getDeferredAttachments() { return deferredAttachments; }
//private:
    RenderAttachment* depthAttachment;
    RenderAttachment* radianceAttachment;
    RenderAttachment* albedoAttachment;
    RenderAttachment* positionAttachment;
    RenderAttachment* normalAttachment;
    RenderAttachment* propertyAttachment;

    std::vector<RenderAttachment*> deferredAttachments;
};
