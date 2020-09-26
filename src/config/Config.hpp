#pragma once

#include <sstream>
#include <string>

#include <rapidjson/document.h>

struct ConfigData
{
    rapidjson::Value root;
    std::string name;
};

class Config
{
protected:
    std::string getConfigString(ConfigData&, const char*);
};
