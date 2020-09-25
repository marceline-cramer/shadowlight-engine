#pragma once

#include "shaders/ShaderModule.hpp"

class MaterialShader
{
public:
    MaterialShader(VkDevice, std::vector<std::string>, std::string);
    ~MaterialShader();

    ShaderStages getStages();
private:
    ShaderModule* vertShader;
    ShaderModule* fragShader;
};
