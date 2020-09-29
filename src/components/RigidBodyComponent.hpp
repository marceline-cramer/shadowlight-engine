#pragma once

#include <iostream>

#include <rapidjson/document.h>

#include "bindings/BulletBinding.hpp"

#include "components/Component.hpp"

class RigidBodyComponent : public TransformComponent
{
public:
    COMPONENT_TYPE("RigidBody");
    
    RigidBodyComponent(BulletBinding*, rapidjson::Value&);
    virtual ~RigidBodyComponent();

    virtual void update(EntityTransform, double) {};
    virtual void finalize(ComponentSet&);
    virtual void createBindings(lua_State*);

    virtual void setTransform(EntityTransform);
    virtual void getTransform(EntityTransform*);
private:
    BulletBinding* bullet;

    btRigidBody* body;
    btScalar mass;
    btCollisionShape* shape;
    btDefaultMotionState* motionState;
};
