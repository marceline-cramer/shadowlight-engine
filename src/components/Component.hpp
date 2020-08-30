#pragma once

#include <map>
#include <set>
#include <string>

#include <lua.hpp>

#define COMPONENT_TYPE(t) static constexpr const char* ComponentType = t; virtual const char* getComponentType() { return ComponentType; };

class Component;
using ComponentSet = std::set<Component*>;
using ComponentMap = std::map<Component*, std::string>;

class Component
{
public:
    virtual ~Component() {};
    virtual void update() {};
    virtual const char* getComponentType() = 0;
    virtual void finalize(ComponentSet&) {};
    virtual void createBindings(lua_State*) {};
private:
};
