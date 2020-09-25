#include "global/ShaderModule.hpp"

ShaderModule::ShaderModule(VkDevice _device, std::string _shaderName, shaderc_shader_kind _shaderKind)
{
    device = _device;
    shaderName = _shaderName;
    shaderKind = _shaderKind;

    compiled = false;
}

ShaderModule::~ShaderModule()
{
    if(compiled) {
        vkDestroyShaderModule(device, shaderModule, nullptr);
    }
}

VkShaderModule ShaderModule::compile()
{
    if(compiled) return shaderModule;

    shaderc::Compiler compiler;
    shaderc::CompileOptions options;

    std::string completeSource = glslSource.str();
    auto spirvModule = compiler.CompileGlslToSpv(completeSource, shaderKind, shaderName.data(), options);

    if(spirvModule.GetCompilationStatus() != shaderc_compilation_status_success) {
        std::ostringstream errorMessage;
        errorMessage << "Shader " << shaderName;
        errorMessage << " compilation failed with ";
        errorMessage << spirvModule.GetErrorMessage();
        throw std::runtime_error(errorMessage.str());
    }

    std::vector<uint32_t> spirv = {spirvModule.cbegin(), spirvModule.cend()};

    VkShaderModuleCreateInfo createInfo{
        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .codeSize = spirv.size() * sizeof(uint32_t),
        .pCode = spirv.data()
    };

    if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create shader module");
    }

    compiled = true;
    return shaderModule;
}
