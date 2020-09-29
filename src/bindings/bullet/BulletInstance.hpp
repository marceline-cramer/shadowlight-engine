#pragma once

#include <bullet/btBulletDynamicsCommon.h>

#include "bindings/Binding.hpp"

#include "global/Filesystem.hpp"

class BulletInstance : public Binding
{
public:
    BulletInstance(Filesystem*);
    ~BulletInstance();
    
    void stepSimulation(double);

    Filesystem* fs;

    btDiscreteDynamicsWorld* world;
private:
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
};
