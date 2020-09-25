#pragma once

#include "shaders/ShaderModule.hpp"

class AmbientLightShader
{
public:
    AmbientLightShader(VkDevice);
    ~AmbientLightShader();

    ShaderStages getStages();
private:
    ShaderModule* vertShader;
    ShaderModule* fragShader;
};
