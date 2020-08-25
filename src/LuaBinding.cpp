#include "LuaBinding.hpp"

LuaBinding::LuaBinding()
{
    // TODO Use lua_newstate and custom allocator
    L = luaL_newstate();
    luaopen_base(L);
}

LuaBinding::~LuaBinding()
{
    lua_close(L);
}


void LuaBinding::update()
{
    
}
