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
    void allocate(AssetHandle<T>&);
    void reap();
private:
    std::vector<T> assets;
};

template<class T>
void AssetPool<T>::allocate(AssetHandle<T>& handle)
{
    for(size_t i = 0; i < assets.size(); i++) {
        auto asset = &assets[i];

        if(asset->refCount < 0) {
            handle.ref(asset);
        }
    }
}

template<class T>
void AssetPool<T>::reap()
{
    // TODO Write AssetPool reaper
}
