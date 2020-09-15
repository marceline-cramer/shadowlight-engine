#pragma once

#include <iostream>

#include <rapidjson/document.h>

#include "bindings/BulletBinding.hpp"

#include "components/Component.hpp"

class RigidBodyComponent : public Component
{
public:
    COMPONENT_TYPE("RigidBody");
    
    RigidBodyComponent(BulletBinding*, rapidjson::Value&);
    virtual ~RigidBodyComponent();

    virtual void update();
    virtual void finalize(ComponentSet&, EntityTransform&);
    virtual void createBindings(lua_State*);
private:
    BulletBinding* bullet;

    EntityTransform* transform;

    btRigidBody* body;
    btScalar mass;
    btCollisionShape* shape;
    btDefaultMotionState* motionState;
};
