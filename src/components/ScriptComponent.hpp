#pragma once

#include <iostream>
#include <string>
#include <map>

#include "assets/AssetHandle.hpp"
#include "assets/ScriptAsset.hpp"

#include "components/Component.hpp"

#include "bindings/LuaBinding.hpp"

#include "global/Scene.hpp"

class ScriptComponent: public Component
{
public:
    ScriptComponent(AssetHandle<ScriptAsset>&);
    virtual ~ScriptComponent() {};

    virtual void update();
    virtual const char* getComponentType() { return ComponentType; };

    void finalize(ComponentSet&);

    static constexpr const char* ComponentType = "script";
private:
    AssetHandle<ScriptAsset> scriptAsset;
    lua_State* thread;
    int selfIndex;
};
