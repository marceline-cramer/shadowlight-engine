#include "bindings/BulletBinding.hpp"

BulletBinding::BulletBinding(Filesystem* fs)
{
    // Create instance
    bulletInstance = new BulletInstance(fs);

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

RigidBodyComponent* BulletBinding::createRigidBody(const char* shapeName)
{
    AssetHandle<ShapeAsset> shape;
    shapePool->load(shapeName, shape);

    return new RigidBodyComponent(bulletInstance, shape);
}
