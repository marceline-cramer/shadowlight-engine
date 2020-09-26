#include "config/PointLightConfig.hpp"

PointLightConfig::PointLightConfig(ConfigData& configData)
{
    position = getConfigVec3(configData, "position");
    flux = getConfigVec3(configData, "flux");
}
