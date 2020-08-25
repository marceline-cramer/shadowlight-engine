#include "AssetHandle.hpp"

AssetHandle::AssetHandle()
{
    asset = nullptr;
}

AssetHandle::~AssetHandle()
{
    deref();
}

Asset* AssetHandle::getAsset()
{
    return asset;
}

void AssetHandle::ref(Asset* _asset)
{
    deref();
    asset = _asset;
    asset->refCount++;
}

void AssetHandle::deref()
{
    if(asset) {
        if(asset->refCount > 0) {
            asset->refCount--;
        }

        asset = nullptr;
    }
}
