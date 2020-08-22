#pragma once

#include "LuaBinding.hpp"
#include "BulletBinding.hpp"
#include "OpenALBinding.hpp"
#include "VulkanBinding.hpp"

class ShadowlightEngine {
public:
    void run();
private:
    LuaBinding lua;
    BulletBinding bullet;
    OpenALBinding openal;
    VulkanBinding vulkan;
};