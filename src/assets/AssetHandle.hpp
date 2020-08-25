#pragma once

#include "assets/Asset.hpp"

template<class T>
class AssetHandle
{
public:
    AssetHandle();
    AssetHandle(const AssetHandle&);
    ~AssetHandle();
    
    T* getAsset();
    void ref(T*);
    void deref();
private:
    T* asset;
};

template<class T>
AssetHandle<T>::AssetHandle()
{
    asset = nullptr;
}

template<class T>
AssetHandle<T>::AssetHandle(const AssetHandle& _handle)
{
    asset = _handle.asset;
    asset->refCount++;
}

template<class T>
AssetHandle<T>::~AssetHandle()
{
    deref();
}

template<class T>
T* AssetHandle<T>::getAsset()
{
    return asset;
}

template<class T>
void AssetHandle<T>::ref(T* _asset)
{
    deref();
    asset = _asset;
    asset->refCount++;
}

template<class T>
void AssetHandle<T>::deref()
{
    if(asset) {
        if(asset->refCount > 0) {
            asset->refCount--;
        }

        asset = nullptr;
    }
}
