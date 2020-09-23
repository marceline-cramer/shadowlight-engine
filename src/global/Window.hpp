#pragma once

#include <stdexcept>
#include <vector>
#include <set>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.h>

#include "input/MouseAxis.hpp"
#include "input/KeyboardAxis.hpp"

class Window
{
public:
    Window();
    ~Window();

    std::vector<const char*> getExtensions();
    void createSurface(VkInstance, VkSurfaceKHR*);
    void update();
    bool shouldQuit() { return quitFlag; };

    InputAxis* getMouseX() { return mouseX; }
    InputAxis* getMouseY() { return mouseY; }
    InputAxis* createKeyboardAxis(SDL_Scancode, SDL_Scancode);
private:
    SDL_Window* window;
    SDL_Surface* surface;

    MouseAxis* mouseX;
    MouseAxis* mouseY;

    std::set<InputAxis*> axes;
    
    bool quitFlag = false;
};
