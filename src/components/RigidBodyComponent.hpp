#pragma once

#include <iostream>

#include <rapidjson/document.h>

#include "assets/AssetHandle.hpp"
#include "assets/ShapeAsset.hpp"

#include "bindings/bullet/BulletInstance.hpp"

#include "components/Component.hpp"

class RigidBodyComponent : public TransformComponent
{
public:
    COMPONENT_TYPE("RigidBody");
    
    RigidBodyComponent(BulletInstance*, btScalar, AssetHandle<ShapeAsset>&);
    virtual ~RigidBodyComponent();

    virtual void update(EntityTransform, double) {};
    virtual void finalize(ComponentSet&) {};
    virtual void createBindings(lua_State*);

    virtual void setTransform(EntityTransform);
    virtual void getTransform(EntityTransform*);
private:
    BulletInstance* bti;

    AssetHandle<ShapeAsset> shapeAsset;

    btRigidBody* body;
    btScalar mass;
    btDefaultMotionState* motionState;
};
