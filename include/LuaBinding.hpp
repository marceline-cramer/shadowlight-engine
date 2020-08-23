#pragma once

#include "lua.hpp"

class LuaBinding
{
public:
    void init();
    void update();
    void exit();
private:
    lua_State* L;
};
