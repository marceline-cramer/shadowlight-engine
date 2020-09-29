#include "bindings/bullet/BulletInstance.hpp"

BulletInstance::BulletInstance()
{
    // Create physics objects
    broadphase = new btDbvtBroadphase();
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    solver = new btSequentialImpulseConstraintSolver();
    world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

    // Initialize physics settings
    world->setGravity(btVector3(0, 0, -9.8));
}

BulletInstance::~BulletInstance()
{
    // Deallocate all physics objects
    delete world;
    delete solver;
    delete broadphase;
    delete dispatcher;
    delete collisionConfiguration;
}

void BulletInstance::stepSimulation(double dt)
{
    world->stepSimulation(dt);
}
