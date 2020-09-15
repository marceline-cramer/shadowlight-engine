#include "global/ShadowlightEngine.hpp"

#include <iostream>

ShadowlightEngine::ShadowlightEngine()
{
    fs = new Filesystem("../test-folder/");
    bullet = new BulletBinding();
    window = new Window();
    vulkan = new VulkanBinding(fs, window);
    oal = new OpenALBinding();
    lua = new LuaBinding(fs);
    scene = new Scene(vulkan, oal, bullet, lua, fs);
}

ShadowlightEngine::~ShadowlightEngine()
{
    delete scene;
    delete lua;
    delete oal;
    delete vulkan;
    delete window;
    delete bullet;
    delete fs;
}

void ShadowlightEngine::run()
{
    scene->load();

    do {
        //std::cout << "Updating..." << std::endl;

        window->update();
        bullet->update();
        lua->update();
        scene->update();
        vulkan->update();
        oal->update();
    } while(!scene->shouldQuit() && !window->shouldQuit());
}
