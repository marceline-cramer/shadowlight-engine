#pragma once

#include <bullet/btBulletDynamicsCommon.h>

#include "config/Config.hpp"

class RigidBodyConfig : public Config
{
public:
    RigidBodyConfig(ConfigData&);

    btScalar mass;
    std::string shape;
};
