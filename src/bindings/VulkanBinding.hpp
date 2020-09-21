#pragma once

#include <iostream>
#include <stdexcept>
#include <set>
#include <vector>

#include <vulkan/vulkan.h>

#include "vk_mem_alloc.h"

#include "bindings/Binding.hpp"

#include "pipelines/Pipeline.hpp"

#include "global/Window.hpp"
#include "global/Filesystem.hpp"

struct QueueFamilyIndices
{
    uint32_t graphicsFamily;
    bool hasGraphicsFamily = false;

    uint32_t presentFamily;
    bool hasPresentFamily = false;

    bool isComplete() {
        return hasGraphicsFamily && hasPresentFamily;
    }
};

struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class VulkanBinding : public Binding
{
public:
    VulkanBinding(Filesystem*, Window*);
    ~VulkanBinding();

    // Utilities for other Vulkan objects to use
    VkShaderModule createShaderModule(const std::vector<char>&);
    uint32_t findMemoryType(uint32_t, VkMemoryPropertyFlags);
    void createBuffer(VkDeviceSize, VkBufferUsageFlags, VkMemoryPropertyFlags, VkBuffer&, VkDeviceMemory&);
    void copyBuffer(VkCommandBuffer, VkBuffer, VkBuffer, VkDeviceSize);
    size_t getSwapchainSize() { return swapChainImages.size(); };
    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer);
    void transitionImageLayout(VkCommandBuffer, VkImage, VkFormat, VkImageLayout, VkImageLayout);
    void copyBufferToImage(VkCommandBuffer, VkBuffer, VkImage, uint32_t, uint32_t);

    void update();
    void render(std::vector<Pipeline*>&);
private:
    // Constants
    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    const bool enableValidationLayers = true;

    // Friend classes
    // Pipelines, Vulkan assets, and Vulkan bindings are tightly coupled,
    // so friend classes are necessary
    friend class MeshFeedForwardPipeline;
    
    friend class MeshAsset;
    friend class MaterialAsset;
    friend class TextureAsset;

    friend class MeshRendererComponent;

    // Convenience functions
    bool checkValidationLayerSupport();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT&);
    void createInstance();
    void setupDebugMessenger();
    void createSurface();
    void pickPhysicalDevice();
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice);
    bool checkDeviceExtensionSupport(VkPhysicalDevice);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice);
    bool isDeviceSuitable(VkPhysicalDevice);
    void createLogicalDevice();
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>&);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>&);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR&);
    void createAllocator();
    void createSwapchain();
    void createImageViews();
    void createRenderPass();
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffers();
    void createSemaphores();

    // Bindings
    Window* window;
    Filesystem* fs;

    // Vulkan data
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkPhysicalDevice physicalDevice;
    VkDevice device;

    VkQueue graphicsQueue;
    VkQueue presentQueue;

    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;

    VkSurfaceKHR surface;

    VkRenderPass mainRenderPass;
    
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;

    VkSemaphore imageAvailableSemaphore;
    VkSemaphore renderFinishedSemaphore;

    // VulkanMemoryAllocator data
    VmaAllocator allocator;
};
