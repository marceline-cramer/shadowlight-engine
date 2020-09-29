#pragma once

#include <sstream>
#include <string>

#include <rapidjson/document.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/hash.hpp>

struct ConfigData
{
    rapidjson::Value root;
    std::string name;
};

class Config
{
protected:
    std::string getConfigString (ConfigData&, const char*);
    glm::vec3   getConfigVec3   (ConfigData&, const char*);
    double      getConfigDouble (ConfigData&, const char*);

    bool checkMember(ConfigData&, const char*);
    bool checkString(ConfigData&, const char*);
    bool checkArray(ConfigData&, const char*);
    bool checkDouble(ConfigData&, const char*);

    void assertMember(ConfigData&, const char*);
    void assertString(ConfigData&, const char*);
    void assertArray(ConfigData&, const char*);
    void assertDouble(ConfigData&, const char*);

    void assertArraySize(ConfigData&, const char*, rapidjson::SizeType);
};
