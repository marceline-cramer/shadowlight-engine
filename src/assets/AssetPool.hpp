#pragma once

#include <stdexcept>
#include <vector>
#include <string>
#include <map>

#include <physfs.h>

#include "assets/Asset.hpp"
#include "assets/AssetHandle.hpp"

#include "bindings/Binding.hpp"

template<class T>
class AssetPool
{
public:
    AssetPool(Binding*);

    void allocate(AssetHandle<T>&);
    void load(const char*, AssetHandle<T>&);
    void reap();
private:
    std::vector<T> assets;
    std::map<std::string, T*> assetCache;
    Binding* binding;
};

template<class T>
AssetPool<T>::AssetPool(Binding* _binding)
{
    binding = _binding;
    assets.resize(1024);
}

template<class T>
void AssetPool<T>::allocate(AssetHandle<T>& handle)
{
    for(size_t i = 0; i < assets.size(); i++) {
        T* asset = &assets[i];

        if(asset->refCount < 0) {
            asset->refCount = 0;
            handle.ref(asset);
            return;
        }
    }

    throw std::runtime_error("Ran out of room in asset pool");
}

template<class T>
void AssetPool<T>::load(const char* fileName, AssetHandle<T>& handle)
{
    auto cached = assetCache.find(fileName);

    if(cached != assetCache.end()) {
        handle.ref(cached->second);
    } else {
        allocate(handle);
        handle.getAsset()->load(static_cast<Binding*>(binding), fileName);
        assetCache.insert(std::pair<std::string, T*>(std::string(fileName), handle.getAsset()));
    }
}

template<class T>
void AssetPool<T>::reap()
{
    // TODO Write AssetPool reaper
    // Remember to remove reaped assets from the cache!
}
