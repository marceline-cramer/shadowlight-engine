#pragma once

#include "config/Config.hpp"

// TODO Cube maps
enum EnvironmentMapType {
    ENVIRONMENT_MAP_TYPE_CYLINDRICAL
};

class EnvironmentMapConfig : public Config
{
public:
    EnvironmentMapConfig(ConfigData&);
private:
    EnvironmentMapType mapType;
    std::string cylinderMap;
};
