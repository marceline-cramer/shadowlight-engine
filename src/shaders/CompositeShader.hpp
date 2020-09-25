#pragma once

#include "shaders/ShaderModule.hpp"

class CompositeShader
{
public:
    CompositeShader(VkDevice);
    ~CompositeShader();

    ShaderStages getStages();
private:
    ShaderModule* vertShader;
    ShaderModule* fragShader;
};
