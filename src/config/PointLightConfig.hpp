#pragma once

#include "config/Config.hpp"

class PointLightConfig : public Config
{
public:
    PointLightConfig(ConfigData&);

    glm::vec3 position;
    glm::vec3 flux;
private:
};
