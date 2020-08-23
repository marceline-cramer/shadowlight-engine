#pragma once

#include "lua.hpp"

class Component
{
public:
    virtual ~Component() {};
    virtual void update() = 0;
    virtual const char* getComponentType() = 0;
    virtual void createBindings(lua_State*) {};
private:
};
