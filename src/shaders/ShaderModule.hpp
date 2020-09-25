#pragma once

#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>

#include <vulkan/vulkan.h>

#include <shaderc/shaderc.hpp>

using ShaderStages = std::vector<VkPipelineShaderStageCreateInfo>;

class ShaderModule
{
public:
    ShaderModule(VkDevice, std::string, shaderc_shader_kind);
    ~ShaderModule();

    void pushCustom(std::string);
    void pushFullscreenQuad();

    VkShaderModule compile();
    VkPipelineShaderStageCreateInfo getStageCreateInfo();
private:
    VkDevice device;
    std::ostringstream glslSource;
    std::string shaderName;
    shaderc_shader_kind shaderKind;
    VkShaderModule shaderModule;
    bool compiled;
};
