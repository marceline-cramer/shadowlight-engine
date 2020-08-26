#pragma once

#include <lua.hpp>

#include "bindings/Binding.hpp"

class LuaBinding : public Binding
{
public:
    LuaBinding();
    ~LuaBinding();
    
    void update();

    lua_State* L;
private:
};
