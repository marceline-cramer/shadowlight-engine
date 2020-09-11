#include "assets/ScriptAsset.hpp"

void ScriptAsset::load(Binding* _lua, const char* fileName)
{
    auto lua = static_cast<LuaBinding*>(_lua);
    
    // Create a new thread
    thread = lua_newthread(lua->L);
    
    // Load the script
    std::string script;
    lua->fs->loadFile(fileName, script);

    // Execute the script
    lua_resume(lua->L, 0);
    luaL_dostring(thread, script.c_str());
    lua_pop(thread, 1);
}

void ScriptAsset::unload()
{
    
}
