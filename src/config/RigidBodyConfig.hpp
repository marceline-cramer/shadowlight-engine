#pragma once

#include <bullet/btBulletDynamicsCommon.h>

#include "config/TransformConfig.hpp"

class RigidBodyConfig : public TransformConfig
{
public:
    RigidBodyConfig(ConfigData&);

    btScalar mass;
    std::string shape;
};
