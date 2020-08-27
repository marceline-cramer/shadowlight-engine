#include "bindings/BulletBinding.hpp"

BulletBinding::BulletBinding()
{
    // Create physics objects
    broadphase = new btDbvtBroadphase();
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    solver = new btSequentialImpulseConstraintSolver();
    world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

    // Initialize physics settings
    world->setGravity(btVector3(0, -9.8, 0));
}

BulletBinding::~BulletBinding()
{
    // Deallocate all physics objects
    delete world;
    delete solver;
    delete broadphase;
    delete dispatcher;
    delete collisionConfiguration;
}


void BulletBinding::update()
{
    // Step the simulation
    world->stepSimulation(1.0f / 60.0f, 10);
}
