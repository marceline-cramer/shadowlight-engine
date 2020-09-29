#include "bindings/BulletBinding.hpp"

BulletBinding::BulletBinding()
{
    // Create instance
    bulletInstance = new BulletInstance();

    // Create asset pools
    shapePool = new AssetPool<ShapeAsset>(bulletInstance);
}

BulletBinding::~BulletBinding()
{
    // Destroy asset pools
    delete shapePool;

    // Destroy instance
    delete bulletInstance;
}


void BulletBinding::update(double dt)
{
    // Step the simulation
    bulletInstance->stepSimulation(dt);
}

RigidBodyComponent* BulletBinding::createRigidBody()
{
    return new RigidBodyComponent(bulletInstance);
}
