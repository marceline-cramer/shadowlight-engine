#pragma once

#include "Asset.hpp"

class AssetHandle
{
public:
    AssetHandle();
    ~AssetHandle();
    
    Asset* getAsset();
    void ref(Asset*);
    void deref();
private:
    Asset* asset;
};
