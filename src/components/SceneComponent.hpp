#pragma once

#include <iostream>

#include "components/Component.hpp"

class Scene;

class SceneComponent : public Component
{
public:
    SceneComponent(Scene*);
    virtual ~SceneComponent() {};

    virtual void update() {};
    virtual const char* getComponentType() { return ComponentType; };
    virtual void createBindings(lua_State*);

    static constexpr const char* ComponentType = "scene";
private:
    Scene* scene;
};
