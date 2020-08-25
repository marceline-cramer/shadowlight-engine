#pragma once

class AssetHandle;

class Asset
{
public:
    virtual ~Asset() {};
private:
    friend class AssetHandle;
    friend class AssetPool;
    Asset* next;
    int refCount;
};
