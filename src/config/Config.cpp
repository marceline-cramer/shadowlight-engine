#include "config/Config.hpp"

std::string Config::getConfigString(ConfigData& configData, const char* member)
{
    assertString(configData, member);
    return configData.root[member].GetString();
}

glm::vec3 Config::getConfigVec3(ConfigData& configData, const char* member)
{
    assertArraySize(configData, member, 3);

    auto vecArray = configData.root[member].GetArray();
    return glm::vec3(
        vecArray[0].GetFloat(),
        vecArray[1].GetFloat(),
        vecArray[2].GetFloat()
    );
}

double Config::getConfigDouble(ConfigData& configData, const char* member)
{
    assertDouble(configData, member);
    return configData.root[member].GetDouble();
}

bool Config::checkMember(ConfigData& configData, const char* member)
{
    if(!configData.root.HasMember(member)) return false;
    return true;
}

bool Config::checkString(ConfigData& configData, const char* member)
{
    if(!checkMember(configData, member)) return false;
    if(!configData.root[member].IsString()) return false;
    return true;
}

bool Config::checkArray(ConfigData& configData, const char* member)
{
    if(!checkMember(configData, member)) return false;
    if(!configData.root[member].IsArray()) return false;
    return true;
}

bool Config::checkDouble(ConfigData& configData, const char* member)
{
    if(!checkMember(configData, member)) return false;
    if(!configData.root[member].IsDouble()) return false;
    return true;
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
    assertMember(configData, member);

    if(!checkString(configData, member)) {
        std::ostringstream errorMessage;
        errorMessage << configData.name;
        errorMessage << "." << member << " must be a string";
        throw std::runtime_error(errorMessage.str());
    }
}

void Config::assertArray(ConfigData& configData, const char* member)
{
    assertMember(configData, member);

    if(!checkArray(configData, member)) {
        std::ostringstream errorMessage;
        errorMessage << configData.name;
        errorMessage << "." << member << " must be an array";
        throw std::runtime_error(errorMessage.str());
    }
}

void Config::assertDouble(ConfigData& configData, const char* member)
{
    assertMember(configData, member);

    if(!checkDouble(configData, member)) {
        std::ostringstream errorMessage;
        errorMessage << configData.name;
        errorMessage << "." << member << " must be a number";
        throw std::runtime_error(errorMessage.str());
    }
}

void Config::assertArraySize(ConfigData& configData, const char* member, rapidjson::SizeType size)
{
    assertArray(configData, member);

    if(configData.root[member].GetArray().Size() != size) {
        std::ostringstream errorMessage;
        errorMessage << configData.name;
        errorMessage << "." << member << " must have length ";
        errorMessage << size;
        throw std::runtime_error(errorMessage.str());
    }
}
