#pragma once

#include "shaders/ShaderModule.hpp"

class PointLightShader
{
public:
    PointLightShader(VulkanInstance*);
    ~PointLightShader();

    ShaderStages getStages();
private:
    ShaderModule* vertShader;
    ShaderModule* fragShader;
};
