#include <iostream>
#include <stdexcept>

#include <physfs.h>

#include "ShadowlightEngine.hpp"

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
