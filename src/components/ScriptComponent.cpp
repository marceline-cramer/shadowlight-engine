#include "components/ScriptComponent.hpp"

ScriptComponent::ScriptComponent(AssetHandle<ScriptAsset>& _scriptAsset, ComponentSet& components)
{
    // Initialize thread
    scriptAsset = _scriptAsset;
    thread = scriptAsset.getAsset()->getThread();

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
}

void ScriptComponent::update()
{
    // Call update function
    lua_getglobal(thread, "update");
    lua_rawgeti(thread, LUA_REGISTRYINDEX, selfIndex);
    lua_call(thread, 1, 0);
}
