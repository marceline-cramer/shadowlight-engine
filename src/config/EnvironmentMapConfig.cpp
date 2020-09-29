#include "config/EnvironmentMapConfig.hpp"

EnvironmentMapConfig::EnvironmentMapConfig(ConfigData& configData)
{
    if(checkMember(configData, "cylinderMap")) {
        mapType = ENVIRONMENT_MAP_TYPE_SPHERICAL;
        sphereMap = getConfigString(configData, "cylinderMap");
    } else {
        throw std::runtime_error("Unrecognized EnvironmentMap type");
    }
}
