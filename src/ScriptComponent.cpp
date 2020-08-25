#include "ScriptComponent.hpp"

void ScriptComponent::init(LuaBinding* lua, ComponentSet& components)
{
    // Create new thread for this script
    thread = lua_newthread(lua->L);

    // Create self table
    lua_createtable(thread, 0, components.size()); 

    // Add component bindings
    for(auto c : components) {
        lua_pushstring(thread, c->getComponentType());
        lua_createtable(thread, 0, 0);
        c->createBindings(thread);
        lua_rawset(thread, -3);
    }

    // Store self table
    selfIndex = luaL_ref(thread, LUA_REGISTRYINDEX);

    // Load the script
    lua_resume(lua->L, 0);
    luaL_dostring(thread, "function update(self) self.flag = not self.flag; print(self.flag) end");
    lua_pop(thread, 1);
}

void ScriptComponent::update()
{
    // Call update function
    lua_getglobal(thread, "update");
    lua_rawgeti(thread, LUA_REGISTRYINDEX, selfIndex);
    lua_call(thread, 1, 0);
}
