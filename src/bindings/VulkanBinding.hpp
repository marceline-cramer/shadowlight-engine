#pragma once

#include <stdexcept>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.h>

#include "bindings/Binding.hpp"

struct QueueFamilyIndices
{
    uint32_t graphicsFamily;
    bool hasGraphicsFamily = false;

    bool isComplete() {
        return hasGraphicsFamily;
    }
};

class VulkanBinding : public Binding
{
public:
    VulkanBinding();
    ~VulkanBinding();

    void update();
private:
    // Convenience functions
    void createInstance();
    void setupDebugMessenger();
    void pickPhysicalDevice();
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice);
    bool isDeviceSuitable(VkPhysicalDevice);
    void createLogicalDevice();

    // SDL structures
    SDL_Window* window;

    // Vulkan data
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkDevice device;

    VkQueue graphicsQueue;
};
