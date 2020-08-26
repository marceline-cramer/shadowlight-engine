#pragma once

#include <lua.hpp>

#include "bindings/Binding.hpp"

#include "global/Filesystem.hpp"

class LuaBinding : public Binding
{
public:
    LuaBinding(Filesystem*);
    ~LuaBinding();
    
    void update();

    lua_State* L;

    Filesystem* fs;
private:
};
