#pragma once

#include "config/Config.hpp"

class TransformConfig : public Config
{
public:
    TransformConfig(ConfigData&);

    glm::vec3 position;
private:
};
