#include "assets/ScriptAsset.hpp"

void ScriptAsset::load(Binding* _lua, const char* fileName)
{
    auto lua = static_cast<LuaBinding*>(_lua);
    
    // Create a new thread
    thread = lua_newthread(lua->L);
    
    // Load the script
    lua_resume(lua->L, 0);
    luaL_dostring(thread, "function update(self) self.flag = not self.flag; print(self.flag) end");
    lua_pop(thread, 1);
}
