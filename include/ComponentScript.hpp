#pragma once

#include <iostream>

#include "Component.hpp"
#include "LuaBinding.hpp"

class ComponentScript: public Component
{
public:
    virtual ~ComponentScript() {};
    virtual void update();
    virtual const char* getComponentType() { return "script"; };

    void init(LuaBinding*);
private:
    lua_State* thread;
};
