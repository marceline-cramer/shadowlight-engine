#pragma once

#include <bullet/btBulletDynamicsCommon.h>

#include "assets/AssetPool.hpp"
#include "assets/ShapeAsset.hpp"

#include "bindings/Binding.hpp"
#include "bindings/bullet/BulletInstance.hpp"

#include "components/RigidBodyComponent.hpp"

#include "global/Filesystem.hpp"

class BulletBinding : public Binding
{
public:
    BulletBinding(Filesystem*);
    ~BulletBinding();
    
    void update(double);

    RigidBodyComponent* createRigidBody(const char*);
private:
    BulletInstance* bulletInstance;

    AssetPool<ShapeAsset>* shapePool;
};
