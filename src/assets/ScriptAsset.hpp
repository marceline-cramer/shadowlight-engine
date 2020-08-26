#pragma once

#include <lua.hpp>

#include "assets/Asset.hpp"

#include "bindings/LuaBinding.hpp"

class ScriptAsset: public Asset
{
public:
    virtual void load(Binding*, const char*);

    lua_State* getThread() { return thread; };
private:
    lua_State* thread;
};
