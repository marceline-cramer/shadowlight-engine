#pragma once

#include <iostream>

#include "components/Component.hpp"

class Scene;

class SceneComponent : public Component
{
public:
    COMPONENT_TYPE("Scene");
    
    SceneComponent(Scene*);
    virtual ~SceneComponent() {};

    virtual void update() {};
    virtual void createBindings(lua_State*);
private:
    Scene* scene;
};
