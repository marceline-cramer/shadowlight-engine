#pragma once

#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>

#include <vulkan/vulkan.h>

#include <shaderc/shaderc.hpp>

#include "bindings/vk/VulkanInstance.hpp"

using ShaderStages = std::vector<VkPipelineShaderStageCreateInfo>;

class ShaderModule
{
public:
    ShaderModule(VulkanInstance*, std::string, shaderc_shader_kind);
    ~ShaderModule();

    void pushCustom(std::string);
    void pushFullscreenQuad();

    VkShaderModule compile();
    VkPipelineShaderStageCreateInfo getStageCreateInfo();
private:
    VulkanInstance* vki;
    std::ostringstream glslSource;
    std::string shaderName;
    shaderc_shader_kind shaderKind;
    VkShaderModule shaderModule;
    bool compiled;
};
