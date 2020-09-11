#pragma once

#include "bindings/Binding.hpp"

class Asset
{
public:
    virtual ~Asset() {};

    virtual void load(Binding*, const char*) = 0;
    virtual void unload() = 0;
private:
    template<class T> friend class AssetHandle;
    template<class T> friend class AssetPool;

    Asset* next = nullptr;
    int refCount = -1;
};
