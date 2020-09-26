#include "config/Config.hpp"

std::string Config::getConfigString(ConfigData& configData, const char* member)
{
    assertMember(configData, member);
    assertString(configData, member);
    return configData.root[member].GetString();
}

glm::vec3 Config::getConfigVec3(ConfigData& configData, const char* member)
{
    assertMember(configData, member);
    assertArray(configData, member);
    assertArraySize(configData, member, 3);

    auto vecArray = configData.root[member].GetArray();
    return glm::vec3(
        vecArray[0].GetFloat(),
        vecArray[1].GetFloat(),
        vecArray[2].GetFloat()
    );
}

void Config::assertMember(ConfigData& configData, const char* member)
{
    if(!configData.root.HasMember(member)) {
        std::ostringstream errorMessage;
        errorMessage << configData.name;
        errorMessage << " must have " << member;
        throw std::runtime_error(errorMessage.str());
    }
}

void Config::assertString(ConfigData& configData, const char* member)
{
    if(!configData.root[member].IsString()) {
        std::ostringstream errorMessage;
        errorMessage << configData.name;
        errorMessage << "." << member << " must be a string";
        throw std::runtime_error(errorMessage.str());
    }
}

void Config::assertArray(ConfigData& configData, const char* member)
{
    if(!configData.root[member].IsArray()) {
        std::ostringstream errorMessage;
        errorMessage << configData.name;
        errorMessage << "." << member << " must be an array";
        throw std::runtime_error(errorMessage.str());
    }
}

void Config::assertArraySize(ConfigData& configData, const char* member, rapidjson::SizeType size)
{
    if(configData.root[member].GetArray().Size() != size) {
        std::ostringstream errorMessage;
        errorMessage << configData.name;
        errorMessage << "." << member << " must have length ";
        errorMessage << size;
        throw std::runtime_error(errorMessage.str());
    }
}
