#pragma once

#include <iostream>
#include <string>
#include <map>

#include "assets/AssetHandle.hpp"
#include "assets/ScriptAsset.hpp"

#include "components/Component.hpp"

#include "bindings/LuaBinding.hpp"

class ScriptComponent: public Component
{
public:
    ScriptComponent(AssetHandle<ScriptAsset>&, ComponentSet&);

    virtual ~ScriptComponent() {};
    virtual void update();
    virtual const char* getComponentType() { return "script"; };
private:
    AssetHandle<ScriptAsset> scriptAsset;
    lua_State* thread;
    int selfIndex;
};
