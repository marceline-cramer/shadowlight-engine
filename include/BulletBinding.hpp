#pragma once

#include <bullet/btBulletDynamicsCommon.h>

class BulletBinding
{
public:
    void init();
    void update();
    void exit();
private:
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* world;
};
