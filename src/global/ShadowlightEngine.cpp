#include "global/ShadowlightEngine.hpp"

#include <iostream>

ShadowlightEngine::ShadowlightEngine()
{
    fs = new Filesystem("../test-folder/");
    bullet = new BulletBinding();
    vulkan = new VulkanBinding();
    openal = new OpenALBinding();
    lua = new LuaBinding(fs);
    scene = new Scene(bullet, lua, fs);
}

ShadowlightEngine::~ShadowlightEngine()
{
    delete scene;
    delete lua;
    delete openal;
    delete vulkan;
    delete bullet;
    delete fs;
}

void ShadowlightEngine::run()
{
    scene->load();

    do {
        //std::cout << "Updating..." << std::endl;

        bullet->update();
        lua->update();
        scene->update();
        vulkan->update();
        openal->update();
    } while(!scene->shouldQuit());
}
