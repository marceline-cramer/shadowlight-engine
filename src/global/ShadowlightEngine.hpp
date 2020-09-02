#pragma once

#include "bindings/LuaBinding.hpp"
#include "bindings/BulletBinding.hpp"
#include "bindings/OpenALBinding.hpp"
#include "bindings/VulkanBinding.hpp"

#include "global/Window.hpp"
#include "global/Scene.hpp"
#include "global/Filesystem.hpp"

class ShadowlightEngine {
public:
    ShadowlightEngine();
    ~ShadowlightEngine();

    void run();
private:
    // Engine bindings
    LuaBinding* lua;
    BulletBinding* bullet;
    OpenALBinding* oal;
    VulkanBinding* vulkan;

    // Engine state
    Window* window;
    Filesystem* fs;
    Scene* scene;
};
