#pragma once

class AssetHandle;

class Asset
{
public:
    virtual ~Asset() {};
private:
    friend class AssetHandle;
    Asset* next;
    int refCount;
};
