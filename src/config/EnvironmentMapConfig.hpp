#pragma once

#include "config/Config.hpp"

// TODO Cube maps
enum EnvironmentMapType {
    ENVIRONMENT_MAP_TYPE_SPHERICAL
};

class EnvironmentMapConfig : public Config
{
public:
    EnvironmentMapConfig(ConfigData&);

    EnvironmentMapType mapType;
    std::string sphereMap;
};
