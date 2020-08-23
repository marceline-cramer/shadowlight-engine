#pragma once

#include "lua.hpp"

class LuaBinding
{
public:
    void init();
    void update();
    void exit();

    lua_State* L;
private:
};
