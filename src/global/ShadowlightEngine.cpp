#include "global/ShadowlightEngine.hpp"

#include <iostream>

ShadowlightEngine::ShadowlightEngine()
{
    bullet = new BulletBinding();
    vulkan = new VulkanBinding();
    openal = new OpenALBinding();
    lua = new LuaBinding();
    scene = new Scene();
}

ShadowlightEngine::~ShadowlightEngine()
{
    delete scene;
    delete lua;
    delete openal;
    delete vulkan;
    delete bullet;
}


void ShadowlightEngine::run()
{
    scene->load(lua);

    do {
        std::cout << "Updating..." << std::endl;

        bullet->update();
        lua->update();
        scene->update();
        vulkan->update();
        openal->update();
    } while(!shouldExit);
}
