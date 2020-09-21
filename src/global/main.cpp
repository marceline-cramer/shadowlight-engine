#include <iostream>
#include <stdexcept>

#include <physfs.h>

#include "global/ShadowlightEngine.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define VMA_IMPLEMENTATION
#include "vk_mem_alloc.h"

int main(int argc, const char* argv[])
{
    PHYSFS_init(argv[0]);
    
    try {
        ShadowlightEngine sle;
        sle.run();
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        PHYSFS_deinit();
        return 1;
    }

    PHYSFS_deinit();
    return 0;
}
