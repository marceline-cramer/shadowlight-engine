#pragma once

class Asset
{
public:
    virtual ~Asset() {};
private:
    template<class T> friend class AssetHandle;
    template<class T> friend class AssetPool;

    Asset* next;
    int refCount;
};
