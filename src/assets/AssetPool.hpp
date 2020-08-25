#pragma once

#include <stdexcept>
#include <vector>

#include <physfs.h>

#include "assets/Asset.hpp"
#include "assets/AssetHandle.hpp"

template<class T>
class AssetPool
{
public:
    void allocate(AssetHandle&);
    void reap();
private:
    std::vector<T> assets;
};
