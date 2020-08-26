#include "bindings/LuaBinding.hpp"

LuaBinding::LuaBinding(Filesystem* _fs)
{
    fs = _fs;
    
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
