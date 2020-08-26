#include "global/ShadowlightEngine.hpp"

#include <iostream>

ShadowlightEngine::ShadowlightEngine()
{
    fs = new Filesystem("../test-package.zip");
    bullet = new BulletBinding();
    vulkan = new VulkanBinding();
    openal = new OpenALBinding();
    lua = new LuaBinding();
    scene = new Scene();

    rapidjson::Document doc;
    fs->loadJson("test.json", doc);
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
