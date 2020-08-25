#pragma once

#include "lua.hpp"

class LuaBinding
{
public:
    LuaBinding();
    ~LuaBinding();
    
    void update();

    lua_State* L;
private:
};
