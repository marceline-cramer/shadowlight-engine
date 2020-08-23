#include "ComponentScript.hpp"

void ComponentScript::init(LuaBinding* lua, std::map<std::string, Component*>& components)
{
    // Create new thread for this script
    thread = lua_newthread(lua->L);

    // Create self table
    lua_createtable(thread, 0, components.size()); 

    // Add component bindings
    for(auto it : components) {
        lua_pushstring(thread, it.first.c_str());
        lua_createtable(thread, 0, 0);
        it.second->createBindings(thread);
        lua_rawset(thread, -3);
    }

    // Store self table
    selfIndex = luaL_ref(thread, LUA_REGISTRYINDEX);

    // Load the script
    lua_resume(lua->L, 0);
    luaL_dostring(thread, "function update(self) self.flag = not self.flag; print(self.flag) end");
    lua_pop(thread, 1);
}

void ComponentScript::update()
{
    // Call update function
    lua_getglobal(thread, "update");
    lua_rawgeti(thread, LUA_REGISTRYINDEX, selfIndex);
    lua_call(thread, 1, 0);
}
