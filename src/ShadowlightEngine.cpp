#include "ShadowlightEngine.hpp"

void ShadowlightEngine::run()
{
    bullet.init();
    vulkan.init();
    openal.init();
    lua.init();

    scene.load();

    while(!shouldExit) {
        bullet.update();
        lua.update();
        scene.update();
        vulkan.update();
        openal.update();
    }

    lua.exit();
    openal.exit();
    vulkan.exit();
    bullet.exit();
}