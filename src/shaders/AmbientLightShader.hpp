#pragma once

#include "shaders/ShaderModule.hpp"

class AmbientLightShader
{
public:
    AmbientLightShader(VulkanInstance*);
    ~AmbientLightShader();

    ShaderStages getStages();
private:
    ShaderModule* vertShader;
    ShaderModule* fragShader;
};
