#pragma once

#include <map>
#include <set>
#include <string>

#include <lua.hpp>

#include "config/Config.hpp"

#include "global/Log.hpp"

#define COMPONENT_TYPE(t) static constexpr const char* ComponentType = t; virtual const char* getComponentType() { return ComponentType; };

class Component;
using ComponentSet = std::set<Component*>;
using ComponentMap = std::map<Component*, std::string>;

struct EntityTransform
{
    glm::vec3 position;
    glm::quat orientation;
};

class Component
{
public:
    virtual ~Component() {};
    virtual const char* getComponentType() = 0;

    virtual void update(EntityTransform, double) = 0;    
    virtual void finalize(ComponentSet&) = 0;
    virtual void createBindings(lua_State*) = 0;
private:
};

class TransformComponent : public Component
{
public:
    virtual ~TransformComponent() {};

    virtual void setTransform(EntityTransform) = 0;
    virtual void getTransform(EntityTransform*) = 0;
};
