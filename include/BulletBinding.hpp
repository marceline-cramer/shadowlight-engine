#pragma once

#include <bullet/btBulletDynamicsCommon.h>

class BulletBinding
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
