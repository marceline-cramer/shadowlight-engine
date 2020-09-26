#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <physfs.h>
#include <rapidjson/document.h>

#include "config/Config.hpp"

class Filesystem
{
public:
    Filesystem(const char*);
    ~Filesystem();

    void loadFile(const char*, std::vector<char>&);
    void loadFile(const char*, std::string&);
    void loadJson(const char*, rapidjson::Document&);

    template<class ConfigType> ConfigType* loadConfig(const char*);
private:
    const char* archive;
};

template<class ConfigType>
ConfigType* Filesystem::loadConfig(const char* fileName)
{
    rapidjson::Document document;
    loadJson(fileName, document);

    ConfigData configData{
        .root = document.GetObject(),
        .name = fileName
    };

    return new ConfigType(configData);
}
