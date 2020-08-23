#pragma once

#include <iostream>
#include <string>
#include <map>

#include "Component.hpp"
#include "LuaBinding.hpp"

class ComponentScript: public Component
{
public:
    virtual ~ComponentScript() {};
    virtual void update();
    virtual const char* getComponentType() { return "script"; };

    void init(LuaBinding*, std::map<std::string, Component*>&);
private:
    lua_State* thread;
    int selfIndex;
};
