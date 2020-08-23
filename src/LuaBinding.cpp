#include "LuaBinding.hpp"

void LuaBinding::init()
{
    // TODO Use lua_newstate and custom allocator
    L = luaL_newstate();
    luaopen_base(L);
}

void LuaBinding::update()
{
    
}

void LuaBinding::exit()
{
    lua_close(L);
}
