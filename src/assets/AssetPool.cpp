#include "assets/AssetPool.hpp"

AssetPool::AssetPool(LuaBinding* _lua)
{
    lua = _lua;
}

void AssetPool::loadScript(AssetHandle& handle, const char* fileName)
{
    auto script = dynamic_cast<ScriptAsset*>(allocate(scripts));

    if(!script) {
        throw std::runtime_error("Ran out of script assets!");
    }

    script->load(lua->L, fileName);
    handle.ref(script);
}

template<class T>
Asset* AssetPool::allocate(AssetSet<T>& assets)
{
    for(size_t i = 0; i < assets.size(); i++) {
        auto asset = assets[i];

        if(asset.refCount < 0) {
            return &assets[i];
        }
    }

    return nullptr;
}
