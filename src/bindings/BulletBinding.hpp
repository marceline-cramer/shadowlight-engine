#pragma once

#include <bullet/btBulletDynamicsCommon.h>

#include "bindings/Binding.hpp"

class BulletBinding : public Binding
{
public:
    BulletBinding();
    ~BulletBinding();
    
    void update();
private:
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* world;
};
