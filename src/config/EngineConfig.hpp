#pragma once

#include <string>

#include "config/Config.hpp"

class EngineConfig : public Config
{
public:
    EngineConfig(ConfigData&);

    std::string firstScene;
};
