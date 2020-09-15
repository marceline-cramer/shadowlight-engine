#pragma once

#include <map>
#include <set>
#include <string>

#include <lua.hpp>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

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
    virtual void update() {};
    virtual const char* getComponentType() = 0;
    virtual void finalize(ComponentSet&, EntityTransform&) {};
    virtual void createBindings(lua_State*) {};
private:
};
