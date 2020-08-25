#include "assets/AssetPool.hpp"

template<class T>
void AssetPool<T>::allocate(AssetHandle& handle)
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
