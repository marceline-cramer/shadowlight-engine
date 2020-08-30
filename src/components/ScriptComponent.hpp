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
    COMPONENT_TYPE("Script");
    
    ScriptComponent(AssetHandle<ScriptAsset>&);
    virtual ~ScriptComponent() {};

    virtual void update();

    virtual void finalize(ComponentSet&);
private:
    AssetHandle<ScriptAsset> scriptAsset;
    lua_State* thread;
    int selfIndex;
};
