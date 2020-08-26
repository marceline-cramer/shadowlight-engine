#pragma once

#include <stdexcept>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.h>

#include "bindings/Binding.hpp"

class VulkanBinding : public Binding
{
public:
    VulkanBinding();
    ~VulkanBinding();

    void update();
private:
    // SDL structures
    SDL_Window* window;

    // Vulkan data
    VkInstance instance;
};
