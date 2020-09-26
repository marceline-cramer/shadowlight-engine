#pragma once

#include "bindings/LuaBinding.hpp"
#include "bindings/BulletBinding.hpp"
#include "bindings/OpenALBinding.hpp"
#include "bindings/VulkanBinding.hpp"

#include "global/Window.hpp"
#include "global/Scene.hpp"
#include "global/Filesystem.hpp"

#include "config/EngineConfig.hpp"

class ShadowlightEngine {
public:
    ShadowlightEngine();
    ~ShadowlightEngine();

    void run();
private:
    // Config
    EngineConfig* engineConfig;

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
