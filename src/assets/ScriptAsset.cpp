#include "assets/ScriptAsset.hpp"

void ScriptAsset::load(lua_State* L, const char* fileName)
{
    // Create a new thread
    thread = lua_newthread(L);
    
    // Load the script
    lua_resume(L, 0);
    luaL_dostring(thread, "function update(self) self.flag = not self.flag; print(self.flag) end");
    lua_pop(thread, 1);
}
