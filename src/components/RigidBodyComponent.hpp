#pragma once

#include <rapidjson/document.h>

#include "bindings/BulletBinding.hpp"

#include "components/Component.hpp"

class RigidBodyComponent : public Component
{
public:
    RigidBodyComponent(BulletBinding*, rapidjson::Value&);
    virtual ~RigidBodyComponent();

    virtual void update();
    virtual void finalize(ComponentSet&);
    virtual void createBindings(lua_State*);
    virtual const char* getComponentType() { return ComponentType; };

    static constexpr const char* ComponentType = "RigidBody";
private:
    BulletBinding* bullet;

    btRigidBody* body;
    btScalar mass;
    btCollisionShape* shape;
    btDefaultMotionState* motionState;
};
