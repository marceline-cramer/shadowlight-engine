#pragma once

#include <stdexcept>
#include <vector>

#include <physfs.h>

#include "Asset.hpp"
#include "AssetHandle.hpp"
#include "ScriptAsset.hpp"
#include "LuaBinding.hpp"

template<class T>
using AssetSet = std::vector<T>;

class AssetPool
{
public:
    AssetPool(LuaBinding*);
    void loadScript(AssetHandle&, const char*);
private:
    // Bindings
    LuaBinding* lua;

    // Asset sets
    AssetSet<ScriptAsset> scripts;

    // Private pool operations
    template<class T>
    Asset* allocate(AssetSet<T>&);
};
