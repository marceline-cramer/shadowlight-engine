#pragma once

#include "shaders/ShaderModule.hpp"

class PointLightShader
{
public:
    PointLightShader(VkDevice);
    ~PointLightShader();

    ShaderStages getStages();
private:
    ShaderModule* vertShader;
    ShaderModule* fragShader;
};
