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

    auto lastUpdate = std::chrono::high_resolution_clock::now();

    do {
        auto thisUpdate = std::chrono::high_resolution_clock::now();
        float dt = std::chrono::duration_cast<std::chrono::nanoseconds>(thisUpdate-lastUpdate).count()/1000000000.0f;

        window->update();
        bullet->update(dt);
        lua->update();
        scene->update();
        vulkan->update();
        oal->update();

        lastUpdate = thisUpdate;
    } while(!scene->shouldQuit() && !window->shouldQuit());
}
