#include "bindings/VulkanBinding.hpp"

VulkanBinding::VulkanBinding(Filesystem* _fs, Window* _window)
{
    fs = _fs;
    window = _window;

    // Setup Vulkan
    vulkanInstance = new VulkanInstance(window, fs);

    device = vulkanInstance->device;
    swapChainExtent = vulkanInstance->swapChainExtent;

    // Setup renderer
    createGBuffers();
    createRenderPass();
    createFramebuffers();
    createCommandBuffers();
    createSemaphores();
}

VulkanBinding::~VulkanBinding()
{
    vkDeviceWaitIdle(device);
    
    vkDestroySemaphore(device, renderFinishedSemaphore, nullptr);
    vkDestroySemaphore(device, imageAvailableSemaphore, nullptr);

    for(auto framebuffer : swapChainFramebuffers) {
        vkDestroyFramebuffer(device, framebuffer, nullptr);
    }

    vkDestroyRenderPass(device, mainRenderPass, nullptr);

    delete gBuffer;

    delete vulkanInstance;
}

VkFormat VulkanBinding::findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features)
{
    for(VkFormat format : candidates) {
        VkFormatProperties props;
        vkGetPhysicalDeviceFormatProperties(vulkanInstance->physicalDevice, format, &props);

        if(tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
            return format;
        } else if(tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
            return format;
        }
    }

    throw std::runtime_error("Failed to find supported format");
}

bool VulkanBinding::hasStencilComponent(VkFormat format)
{
    return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
}

void VulkanBinding::createGBuffers()
{
    auto width = swapChainExtent.width;
    auto height = swapChainExtent.height;

    gBuffer = new GBuffer(vulkanInstance, width, height);
}

void VulkanBinding::createRenderPass()
{
    // Create attachment data
    VkAttachmentDescription presentDescription{
        .format = vulkanInstance->swapChainImageFormat,
        .samples = VK_SAMPLE_COUNT_1_BIT,
        .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
        .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
        .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
    };

    VkAttachmentReference presentRef{
        .attachment = 0,
        .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
    };

    VkAttachmentDescription depthDescription{
        .format = gBuffer->depthAttachment->getFormat(),
        .samples = VK_SAMPLE_COUNT_1_BIT,
        .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
        .storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
        .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
        .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
    };

    VkAttachmentReference depthRef{
        .attachment = 1,
        .layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
    };

    VkAttachmentDescription radianceDescription{
        .format = gBuffer->radianceAttachment->getFormat(),
        .samples = VK_SAMPLE_COUNT_1_BIT,
        .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
        .storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
        .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
    };

    VkAttachmentReference radianceTargetRef{
        .attachment = 2,
        .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
    };

    VkAttachmentReference radianceInputRef{
        .attachment = 2,
        .layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
    };

    std::vector<VkAttachmentDescription> attachments = {
        presentDescription,
        depthDescription,
        radianceDescription
    };

    std::vector<VkAttachmentReference> gTargetRef;
    std::vector<VkAttachmentReference> gInputRef;

    auto gAttachments = gBuffer->getDeferredAttachments();
    for(uint32_t i = 0; i < gAttachments.size(); i++) {
        attachments.push_back({
            .format = gAttachments[i]->getFormat(),
            .samples = VK_SAMPLE_COUNT_1_BIT,
            .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
            .storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
            .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
            .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
            .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            .finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
        });

        gTargetRef.push_back({
            .attachment = 3 + i,
            .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
        });

        gInputRef.push_back({
            .attachment = 3 + i,
            .layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
        });
    }

    VkSubpassDescription deferredPass = {
        .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
        .colorAttachmentCount = static_cast<uint32_t>(gTargetRef.size()),
        .pColorAttachments = gTargetRef.data(),
        .pDepthStencilAttachment = &depthRef
    };

    VkSubpassDescription lightingPass = {
        .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
        .inputAttachmentCount = static_cast<uint32_t>(gInputRef.size()),
        .pInputAttachments = gInputRef.data(),
        .colorAttachmentCount = 1,
        .pColorAttachments = &radianceTargetRef,
        .pDepthStencilAttachment = &depthRef
    };

    VkSubpassDescription compositePass = {
        .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
        .inputAttachmentCount = 1,
        .pInputAttachments = &radianceInputRef,
        .colorAttachmentCount = 1,
        .pColorAttachments = &presentRef,
        .pDepthStencilAttachment = &depthRef
    };

    VkSubpassDescription overlayPass = {
        .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
        .colorAttachmentCount = 1,
        .pColorAttachments = &presentRef,
        .pDepthStencilAttachment = &depthRef
    };

    std::vector<VkSubpassDescription> subpasses = {
        deferredPass,
        lightingPass,
        compositePass,
        overlayPass
    };

    std::vector<VkSubpassDependency> subpassDependencies;

    // Wait until G-Buffer is ready before drawing geometry
    subpassDependencies.push_back({
        .srcSubpass = VK_SUBPASS_EXTERNAL,
        .dstSubpass = 0,
        .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .srcAccessMask = 0,
        .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT
    });

    // Wait until deferred rendering is done before lighting
    subpassDependencies.push_back({
        .srcSubpass = 0,
        .dstSubpass = 1,
        .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .srcAccessMask = 0,
        .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT
    });

    // Wait until lighting is done before compositing
    subpassDependencies.push_back({
        .srcSubpass = 1,
        .dstSubpass = 2,
        .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .srcAccessMask = 0,
        .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT
    });

    // Wait until compositing is done before adding overlays
    subpassDependencies.push_back({
        .srcSubpass = 2,
        .dstSubpass = 3,
        .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .srcAccessMask = 0,
        .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT
    });

    VkRenderPassCreateInfo renderPassInfo{
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        .attachmentCount = static_cast<uint32_t>(attachments.size()),
        .pAttachments = attachments.data(),
        .subpassCount = static_cast<uint32_t>(subpasses.size()),
        .pSubpasses = subpasses.data(),
        .dependencyCount = static_cast<uint32_t>(subpassDependencies.size()),
        .pDependencies = subpassDependencies.data()
    };

    if(vkCreateRenderPass(device, &renderPassInfo, nullptr, &mainRenderPass) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create render pass");
    }
}

void VulkanBinding::createFramebuffers()
{
    swapChainFramebuffers.resize(vulkanInstance->swapChainImageViews.size());

    for(size_t i = 0; i < vulkanInstance->swapChainImageViews.size(); i++) {
        std::vector<VkImageView> attachments = {
            vulkanInstance->swapChainImageViews[i],
            gBuffer->depthAttachment->getImageView(),
            gBuffer->radianceAttachment->getImageView()
        };

        auto gAttachments = gBuffer->getDeferredAttachments();
        for(auto attachment : gAttachments) {
            attachments.push_back(attachment->getImageView());
        }

        VkFramebufferCreateInfo framebufferInfo{
            .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
            .renderPass = mainRenderPass,
            .attachmentCount = static_cast<uint32_t>(attachments.size()),
            .pAttachments = attachments.data(),
            .width = swapChainExtent.width,
            .height = swapChainExtent.height,
            .layers = 1
        };

        if(vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create framebuffer");
        }
    }
}

void VulkanBinding::createCommandBuffers()
{
    commandBuffers.resize(swapChainFramebuffers.size());

    VkCommandBufferAllocateInfo allocInfo{
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .commandPool = vulkanInstance->commandPool,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = (uint32_t) commandBuffers.size()
    };

    if(vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
        throw std::runtime_error("Failed to allocate command buffers");
    }
}

void VulkanBinding::createSemaphores()
{
    VkSemaphoreCreateInfo semaphoreInfo{
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO
    };

    if(vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create image available semaphore");
    }

    if(vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphore) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create render finished semaphore");
    }
}

VkShaderModule VulkanBinding::createShaderModule(const std::vector<uint32_t>& code)
{
    VkShaderModuleCreateInfo createInfo{
        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .codeSize = code.size() * sizeof(uint32_t),
        .pCode = code.data()
    };

    VkShaderModule shaderModule;
    if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
        throw std::runtime_error("failed to create shader module!");
    }

    return shaderModule;
}

uint32_t VulkanBinding::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(vulkanInstance->physicalDevice, &memProperties);

    for(uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("Failed to find suitable memory type");
}

void VulkanBinding::update()
{

}

void VulkanBinding::render(PipelineSet& deferredPipelines, PipelineSet& lightingPipelines, Pipeline* compositePipeline, PipelineSet& overlayPipelines)
{
    auto it = cameras.find("main");
    if(it == cameras.end()) {
        throw std::runtime_error("No main camera");
    }
    auto mainCamera = it->second;

    // Acquire swapchain image
    uint32_t imageIndex;
    vkAcquireNextImageKHR(device, vulkanInstance->swapChain, UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

    auto commandBuffer = commandBuffers[imageIndex];
    auto framebuffer = swapChainFramebuffers[imageIndex];

    // Begin this frame's command buffer
    VkCommandBufferBeginInfo beginInfo{
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT
    };

    if(vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("Failed to begin command buffer");
    }

    std::array<VkClearValue, 7> clearValues;
    // Swapchain
    clearValues[0].color = {0.2, 0.0, 0.0, 1.0};
    // Shared depth
    clearValues[1].depthStencil = {1.0, 0};
    // Radiance
    clearValues[2].color = {0.0, 0.0, 0.0, 1.0};
    // Albedo: Clear to magenta to make lighting errors visible
    clearValues[3].color = {1.0, 0.0, 1.0, 1.0};
    // Position
    clearValues[4].color = {0.0, 0.0, 0.0, 1.0};
    // Normal
    clearValues[5].color = {0.0, 0.0, 1.0, 1.0};
    // Properties
    clearValues[6].color = {0.0, 1.0, 0.5, 1.0};

    VkRenderPassBeginInfo renderPassInfo{
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
        .renderPass = mainRenderPass,
        .framebuffer = framebuffer,
        .renderArea = {
            .offset = {0, 0},
            .extent = swapChainExtent
        },
        .clearValueCount = static_cast<uint32_t>(clearValues.size()),
        .pClearValues = clearValues.data()
    };

    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    // Deferred pass
    for(auto p : deferredPipelines) {
        p->render(commandBuffer, mainCamera);
    }
    vkCmdNextSubpass(commandBuffer, VK_SUBPASS_CONTENTS_INLINE);

    // Lighting pass
    for(auto p : lightingPipelines) {
        p->render(commandBuffer, mainCamera);
    }
    vkCmdNextSubpass(commandBuffer, VK_SUBPASS_CONTENTS_INLINE);

    // Composite pass
    compositePipeline->render(commandBuffer, mainCamera);
    vkCmdNextSubpass(commandBuffer, VK_SUBPASS_CONTENTS_INLINE);

    // Overlay pass
    for(auto p : overlayPipelines) {
        p->render(commandBuffer, mainCamera);
    }
    vkCmdEndRenderPass(commandBuffer);

    // End the command buffer
    if(vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("Failed to end command buffer");
    }

    // Submit the command buffer
    VkSemaphore waitSemaphores[] = {imageAvailableSemaphore};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    VkSemaphore signalSemaphores[] = {renderFinishedSemaphore};

    VkSubmitInfo submitInfo{
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = waitSemaphores,
        .pWaitDstStageMask = waitStages,
        .commandBufferCount = 1,
        .pCommandBuffers = &commandBuffer,
        .signalSemaphoreCount = 1,
        .pSignalSemaphores = signalSemaphores
    };

    if(vkQueueSubmit(vulkanInstance->graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS) {
        throw std::runtime_error("Failed to submit draw command buffer");
    }

    // Present the frame
    VkSwapchainKHR swapChains[] = {vulkanInstance->swapChain};

    VkPresentInfoKHR presentInfo{
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = signalSemaphores,
        .swapchainCount = 1,
        .pSwapchains = swapChains,
        .pImageIndices = &imageIndex,
        .pResults = nullptr
    };

    vkQueuePresentKHR(vulkanInstance->presentQueue, &presentInfo);

    // TODO Better frame synchronization
    vkQueueWaitIdle(vulkanInstance->presentQueue);
}

CameraComponent* VulkanBinding::createCamera(const char* target)
{
    if(cameras.find(target) != cameras.end()) {
        std::ostringstream errorMessage;
        errorMessage << "Camera target ";
        errorMessage << target;
        errorMessage << " already occupied";
        throw std::runtime_error(errorMessage.str());
    }

    auto camera = new CameraComponent(target, &cameras, swapChainExtent.width / (float) swapChainExtent.height);
    return camera;
}
