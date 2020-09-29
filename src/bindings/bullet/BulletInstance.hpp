#pragma once

#include <bullet/btBulletDynamicsCommon.h>

#include "bindings/Binding.hpp"

class BulletInstance : public Binding
{
public:
    BulletInstance();
    ~BulletInstance();
    
    void stepSimulation(double);

    btDiscreteDynamicsWorld* world;
private:
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
};
