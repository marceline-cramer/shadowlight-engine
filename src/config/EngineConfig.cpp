#include "config/EngineConfig.hpp"

EngineConfig::EngineConfig(ConfigData& configData)
{
    firstScene = getConfigString(configData, "firstScene");
}
