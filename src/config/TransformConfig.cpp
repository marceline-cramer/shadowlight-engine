#include "config/TransformConfig.hpp"

TransformConfig::TransformConfig(ConfigData& configData)
{
    // TODO Quaternion loads from config
    position = getConfigVec3(configData, "position");
}
