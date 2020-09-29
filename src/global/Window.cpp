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

    // Setup input
    SDL_SetRelativeMouseMode(SDL_TRUE);
    // TODO Input config JSON
    mouseX = new MouseAxis(0.6);
    mouseY = new MouseAxis(0.6);

    axes.insert(mouseX);
    axes.insert(mouseY);
}

Window::~Window()
{
    for(auto axis : axes) {
        delete axis;
    }

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

void Window::update(double dt)
{
    SDL_Event e;

    int relx = 0;
    int rely = 0;

    SDL_PumpEvents();
    while(SDL_PollEvent(&e) != 0)
    {
        switch(e.type)
        {
        case SDL_QUIT:
            quitFlag = true;
            break;
        case SDL_MOUSEMOTION:
            relx += e.motion.xrel;
            rely += e.motion.yrel;
            break;
        }
    }

    mouseX->updateRelative(relx);
    mouseY->updateRelative(rely);

    for(auto axis : axes) {
        axis->process(dt);
    }
}

InputAxis* Window::createKeyboardAxis(SDL_Scancode negKey, SDL_Scancode posKey)
{
    auto axis = new KeyboardAxis(negKey, posKey);
    axes.insert(axis);
    return axis;
}
