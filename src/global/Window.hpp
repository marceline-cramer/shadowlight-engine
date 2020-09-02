#pragma once

#include <stdexcept>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.h>

class Window
{
public:
    Window();
    ~Window();

    std::vector<const char*> getExtensions();
    void createSurface(VkInstance, VkSurfaceKHR*);
    void update();
    bool shouldQuit() { return quitFlag; };
private:
    SDL_Window* window;
    SDL_Surface* surface;
    
    bool quitFlag = false;
};
