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

    void _load(Binding* b, const char* f) { refCount = 0; loaded = true; load(b, f); };
    void _unload() { refCount = 0; loaded = false; unload(); };

    Asset* next = nullptr;
    int refCount = 0;
    bool loaded = false;
};
