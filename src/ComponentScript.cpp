#include "ComponentScript.hpp"

void ComponentScript::init(LuaBinding* lua)
{
    thread = lua_newthread(lua->L);
    lua_resume(lua->L, 0);
    luaL_dostring(thread, "function update() print('testing, testing') end");
    lua_pop(lua->L, 1);
}

void ComponentScript::update()
{
    lua_getglobal(thread, "update");
    lua_call(thread, 0, 0);
}
