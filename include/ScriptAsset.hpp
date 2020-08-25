#pragma once

#include <lua.hpp>

#include "Asset.hpp"

class ScriptAsset: public Asset
{
public:
    void load(lua_State*, const char*);
private:
};
