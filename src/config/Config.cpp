#include "config/Config.hpp"

std::string Config::getConfigString(ConfigData& configData, const char* member)
{
    if(!configData.root.HasMember(member)) {
        std::ostringstream errorMessage;
        errorMessage << configData.name;
        errorMessage << " must have " << member;
        throw std::runtime_error(errorMessage.str());
    }

    if(!configData.root[member].IsString()) {
        std::ostringstream errorMessage;
        errorMessage << configData.name;
        errorMessage << "." << member << " must be a string";
        throw std::runtime_error(errorMessage.str());
    }

    return configData.root[member].GetString();
}
