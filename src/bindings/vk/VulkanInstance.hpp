#pragma once

#include <vector>
#include <iostream>

#include <vulkan/vulkan.h>

#include <vk_mem_alloc.h>

#include "bindings/Binding.hpp"

#include "global/Window.hpp"
#include "global/Filesystem.hpp"
#include "global/Log.hpp"

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

class VulkanInstance : public Binding
{
public:
    VulkanInstance(Window*, Filesystem*);
    ~VulkanInstance();

    VkFormat findSupportedFormat(const std::vector<VkFormat>&, VkImageTiling, VkFormatFeatureFlags);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void createImage(uint32_t, uint32_t, VkFormat, VkImageTiling, VkImageUsageFlags, VkMemoryPropertyFlags, VkImage&, VkDeviceMemory&);
    void createImageView(VkImage, VkFormat, VkImageAspectFlags, VkImageView&);
    void createSampler(VkSampler&);
    void createBuffer(VkDeviceSize, VkBufferUsageFlags, VkMemoryPropertyFlags, VkBuffer&, VkDeviceMemory&);
    void copyBuffer(VkCommandBuffer, VkBuffer, VkBuffer, VkDeviceSize);
    void stageBuffer(VkBuffer, VkDeviceSize, void*);
    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer);
    void transitionImageLayout(VkCommandBuffer, VkImage, VkFormat, VkImageLayout, VkImageLayout);
    void copyBufferToImage(VkCommandBuffer, VkBuffer, VkImage, uint32_t, uint32_t);

    void nameHandle(uint64_t, VkObjectType, const char*);

    VkExtent2D getSwapChainExtent() { return swapChainExtent; }

    VkDevice device;
private:
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
    void createAllocator();
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>&);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>&);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR&);
    void createSwapchain();
    void createImageViews();
    void createCommandPool();

    // TODO Vulkan object wrapper classes
    friend class VulkanBinding;
    friend class RenderAttachment;

    friend class TextureAsset;
    friend class MeshAsset;

    friend class SkyboxComponent;

    friend class SkyboxShader;

    // Constants
    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    const bool enableValidationLayers = true;

    // Bindings
    Window* window;
    Filesystem* fs;

    // Vulkan data
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice;

    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkCommandPool commandPool;

    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    std::vector<VkImageView> swapChainImageViews;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;

    // Vulkan function pointers
    PFN_vkSetDebugUtilsObjectNameEXT SetDebugUtilsObjectNameEXT = nullptr;

    // VulkanMemoryAllocator data
    VmaAllocator allocator;
};
