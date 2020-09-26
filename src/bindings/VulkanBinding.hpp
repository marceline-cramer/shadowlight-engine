#pragma once

#include <iostream>
#include <stdexcept>
#include <set>
#include <vector>
#include <sstream>

#include <vulkan/vulkan.h>

#include "bindings/Binding.hpp"
#include "bindings/vk/GBuffer.hpp"
#include "bindings/vk/VulkanInstance.hpp"

#include "components/CameraComponent.hpp"

#include "pipelines/Pipeline.hpp"

#include "global/Window.hpp"
#include "global/Filesystem.hpp"

class VulkanBinding : public Binding
{
public:
    VulkanBinding(Filesystem*, Window*);
    ~VulkanBinding();

    // Utilities for other Vulkan objects to use
    VkShaderModule createShaderModule(const std::vector<uint32_t>&);
    uint32_t findMemoryType(uint32_t, VkMemoryPropertyFlags);
    void createBuffer(VkDeviceSize, VkBufferUsageFlags, VkMemoryPropertyFlags, VkBuffer&, VkDeviceMemory&);
    void copyBuffer(VkCommandBuffer, VkBuffer, VkBuffer, VkDeviceSize);
    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer);
    void transitionImageLayout(VkCommandBuffer, VkImage, VkFormat, VkImageLayout, VkImageLayout);
    void copyBufferToImage(VkCommandBuffer, VkBuffer, VkImage, uint32_t, uint32_t);

    VulkanInstance* getInstance() { return vulkanInstance; }
    GBuffer* getGBuffer() { return gBuffer; }
    VkImageView getRadianceView() { return gBuffer->radianceAttachment->getImageView(); }

    void update();
    void render(PipelineSet&, PipelineSet&, Pipeline*, PipelineSet&);

    CameraComponent* createCamera(const char*);
private:
    // Friend classes
    // Pipelines, Vulkan assets, and Vulkan bindings are tightly coupled,
    // so friend classes are necessary
    friend class MeshFeedForwardPipeline;
    friend class CompositePipeline;
    friend class AmbientLightPipeline;
    friend class PointLightPipeline;
    
    friend class MeshAsset;
    friend class MaterialAsset;
    friend class TextureAsset;

    friend class MeshRendererComponent;
    friend class PointLightComponent;

    // TODO You're better than this, Mars.
    VkDevice device;
    VkExtent2D swapChainExtent;

    // Convenience functions
    VkFormat findSupportedFormat(const std::vector<VkFormat>&, VkImageTiling, VkFormatFeatureFlags);
    bool hasStencilComponent(VkFormat);
    void createGBuffers();
    void createRenderPass();
    void createFramebuffers();
    void createCommandBuffers();
    void createSemaphores();

    // Bindings
    Window* window;
    Filesystem* fs;

    // Vulkan data
    VulkanInstance* vulkanInstance;

    std::vector<VkCommandBuffer> commandBuffers;

    std::vector<VkFramebuffer> swapChainFramebuffers;

    VkRenderPass mainRenderPass;
    GBuffer* gBuffer;
    CameraMap cameras;

    VkSemaphore imageAvailableSemaphore;
    VkSemaphore renderFinishedSemaphore;
};
