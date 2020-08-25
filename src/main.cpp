#include <iostream>
#include <stdexcept>

#include "ShadowlightEngine.hpp"

int main()
{
    try {
        ShadowlightEngine sle;
        sle.run();
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
