#include "global/ShadowlightEngine.hpp"

#include <iostream>

ShadowlightEngine::ShadowlightEngine()
{
    fs = new Filesystem("../test-folder/");
    bullet = new BulletBinding();
    vulkan = new VulkanBinding();
    oal = new OpenALBinding();
    lua = new LuaBinding(fs);
    scene = new Scene(oal, bullet, lua, fs);
}

ShadowlightEngine::~ShadowlightEngine()
{
    delete scene;
    delete lua;
    delete oal;
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
        oal->update();
    } while(!scene->shouldQuit());
}
