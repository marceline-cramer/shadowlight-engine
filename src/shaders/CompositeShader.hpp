#pragma once

#include "shaders/ShaderModule.hpp"

class CompositeShader
{
public:
    CompositeShader(VulkanInstance*);
    ~CompositeShader();

    ShaderStages getStages();
private:
    ShaderModule* vertShader;
    ShaderModule* fragShader;
};
