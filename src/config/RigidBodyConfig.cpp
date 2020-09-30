#include "config/RigidBodyConfig.hpp"

RigidBodyConfig::RigidBodyConfig(ConfigData& configData) : TransformConfig(configData)
{
    // Default to static (zero mass)
    if(!checkDouble(configData, "mass")) {
        mass = 0.0;
    } else {
        mass = getConfigDouble(configData, "mass");
    }
    
    shape = getConfigString(configData, "shape");
}
