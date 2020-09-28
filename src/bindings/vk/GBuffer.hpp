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
    VkPipelineViewportStateCreateInfo getViewportState() { return viewportState; }
    VkPipelineDepthStencilStateCreateInfo getDepthStencilState() { return depthStencilState; }
    VkPipelineMultisampleStateCreateInfo getMultisampleState() { return multisampleState; }
    VkPipelineColorBlendStateCreateInfo getColorBlendState() { return colorBlendState; }
//private:
    RenderAttachment* depthAttachment;
    RenderAttachment* radianceAttachment;
    RenderAttachment* albedoAttachment;
    RenderAttachment* positionAttachment;
    RenderAttachment* normalAttachment;
    RenderAttachment* propertyAttachment;

    std::vector<RenderAttachment*> deferredAttachments;

    VkPipelineViewportStateCreateInfo viewportState;
        VkViewport viewport;
        VkRect2D scissor;
    VkPipelineDepthStencilStateCreateInfo depthStencilState;
    VkPipelineMultisampleStateCreateInfo multisampleState;
    VkPipelineColorBlendStateCreateInfo colorBlendState;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
};
