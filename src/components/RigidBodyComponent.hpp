#pragma once

#include <iostream>

#include <rapidjson/document.h>

#include "bindings/bullet/BulletInstance.hpp"

#include "components/Component.hpp"

class RigidBodyComponent : public TransformComponent
{
public:
    COMPONENT_TYPE("RigidBody");
    
    RigidBodyComponent(BulletInstance*);
    virtual ~RigidBodyComponent();

    virtual void update(EntityTransform, double) {};
    virtual void finalize(ComponentSet&);
    virtual void createBindings(lua_State*);

    virtual void setTransform(EntityTransform);
    virtual void getTransform(EntityTransform*);
private:
    BulletInstance* bti;

    btRigidBody* body;
    btScalar mass;
    btCollisionShape* shape;
    btDefaultMotionState* motionState;
};
