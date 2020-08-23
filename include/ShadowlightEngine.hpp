#pragma once

#include "LuaBinding.hpp"
#include "BulletBinding.hpp"
#include "OpenALBinding.hpp"
#include "VulkanBinding.hpp"

#include "Scene.hpp"

class ShadowlightEngine {
public:
    void run();
private:
    // Engine bindings
    LuaBinding lua;
    BulletBinding bullet;
    OpenALBinding openal;
    VulkanBinding vulkan;

    // Engine state
    Scene scene;
    bool shouldExit = true;
};
