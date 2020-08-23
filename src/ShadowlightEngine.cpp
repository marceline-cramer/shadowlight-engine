#include "ShadowlightEngine.hpp"

#include <iostream>

void ShadowlightEngine::run()
{
    bullet.init();
    vulkan.init();
    openal.init();
    lua.init();

    scene.load(&lua);

    do {
        std::cout << "Updating..." << std::endl;

        bullet.update();
        lua.update();
        scene.update();
        vulkan.update();
        openal.update();
    } while(!shouldExit);

    lua.exit();
    openal.exit();
    vulkan.exit();
    bullet.exit();
}
