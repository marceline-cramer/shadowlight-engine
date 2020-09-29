#pragma once

#include <bullet/btBulletDynamicsCommon.h>

#include "assets/Asset.hpp"

#include "bindings/bullet/BulletInstance.hpp"

#include "config/ShapeConfig.hpp"

class ShapeAsset : public Asset
{
public:
    virtual void load(Binding*, const char*);
    virtual void unload();

    btCollisionShape* shape;
private:
    BulletInstance* bti;

    ShapeConfig* config;
};
