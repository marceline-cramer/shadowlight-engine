#pragma once

#include <bullet/btBulletDynamicsCommon.h>

#include "config/Config.hpp"

// TODO Compound (recursive) shapes
// TODO COLLADA loader

enum ShapeType {
    SHAPE_TYPE_PLANE,
    SHAPE_TYPE_SPHERE
};

class ShapeConfig : public Config
{
public:
    ShapeConfig(ConfigData&);

    ShapeType shapeType;
    btVector3 shapeVector;
    btScalar shapeScalar;
private:
};
