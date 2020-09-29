#pragma once

#include <iostream>

#include "components/Component.hpp"

class Scene;

class SceneComponent : public Component
{
public:
    COMPONENT_TYPE("Scene");
    
    SceneComponent(Scene*);
    ~SceneComponent() {};

    virtual void update(EntityTransform, double) {};
    virtual void createBindings(lua_State*);
    virtual void finalize(ComponentSet&) {};
private:
    Scene* scene;
};
