#pragma once

#include <vector>

#include <lua.hpp>

#include "assets/Asset.hpp"

#include "bindings/LuaBinding.hpp"

#include "global/Filesystem.hpp"

class ScriptAsset: public Asset
{
public:
    virtual void load(Binding*, const char*);
    virtual void unload();

    lua_State* getThread() { return thread; };
private:
    lua_State* thread;
};
