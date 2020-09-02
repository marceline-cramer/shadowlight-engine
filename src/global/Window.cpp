#include "Window.hpp"

Window::Window()
{
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Failure to initialize SDL");
    }

    // Create SDL window
    window = SDL_CreateWindow("SDL Tutorial",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              800, 600,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);
    if(!window) {
        throw std::runtime_error("Failed to create SDL window");
    }

    // Clear surface
    surface = SDL_GetWindowSurface(window);
    SDL_FillRect(surface, nullptr, 0);
    SDL_UpdateWindowSurface(window);
}

Window::~Window()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

std::vector<const char*> Window::getExtensions()
{
    uint32_t extensionCount;
    SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, nullptr);
    std::vector<const char*> extensionNames(extensionCount);
    SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, extensionNames.data());
    return extensionNames;
}

void Window::createSurface(VkInstance instance, VkSurfaceKHR* surface)
{
    if(SDL_Vulkan_CreateSurface(window, instance, surface) != SDL_TRUE) {
        throw std::runtime_error("Failed to create window surface");
    }
}

void Window::update()
{
    SDL_Event e;

    while(SDL_PollEvent(&e) != 0)
    {
        if(e.type == SDL_QUIT)
        {
            quitFlag = true;
        }
    }
}
