#pragma once

#include <iostream>
#include <string>
#include <map>

#include "components/Component.hpp"
#include "bindings/LuaBinding.hpp"

class ScriptComponent: public Component
{
public:
    virtual ~ScriptComponent() {};
    virtual void update();
    virtual const char* getComponentType() { return "script"; };

    void init(LuaBinding*, ComponentSet&);
private:
    lua_State* thread;
    int selfIndex;
};
