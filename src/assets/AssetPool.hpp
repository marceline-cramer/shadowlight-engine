#pragma once

#include <stdexcept>
#include <vector>

#include <physfs.h>

#include "assets/Asset.hpp"
#include "assets/AssetHandle.hpp"
#include "assets/ScriptAsset.hpp"

#include "bindings/LuaBinding.hpp"

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
