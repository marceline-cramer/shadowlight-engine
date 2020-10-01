#include "shaders/ShaderModule.hpp"

ShaderModule::ShaderModule(VulkanInstance* _vki, std::string _shaderName, shaderc_shader_kind _shaderKind)
{
    vki = _vki;
    shaderName = _shaderName;
    shaderKind = _shaderKind;

    compiled = false;

    glslSource << "#version 450" << std::endl;
    glslSource << "#extension GL_ARB_separate_shader_objects : enable" << std::endl;
}

ShaderModule::~ShaderModule()
{
    if(compiled) {
        vkDestroyShaderModule(vki->device, shaderModule, nullptr);
    }
}

void ShaderModule::pushCustom(std::string code)
{
    glslSource << code << std::endl;
}

void ShaderModule::pushFullscreenQuad()
{
    glslSource << R"""(
layout(location = 0) out vec2 fragTexCoord;

vec2 positions[4] = vec2[](
    vec2( 1.0, -1.0),
    vec2(-1.0, -1.0),
    vec2( 1.0,  1.0),
    vec2(-1.0,  1.0)
);

vec2 texCoords[4] = vec2[](
    vec2(1.0, 0.0),
    vec2(0.0, 0.0),
    vec2(1.0, 1.0),
    vec2(0.0, 1.0)
);

void main() {
    gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);
    fragTexCoord = texCoords[gl_VertexIndex];
}
    )""" << std::endl;
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

    if(vkCreateShaderModule(vki->device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create shader module");
    }
    vki->nameHandle((uint64_t)shaderModule, VK_OBJECT_TYPE_SHADER_MODULE, shaderName.data());

    compiled = true;
    return shaderModule;
}

VkPipelineShaderStageCreateInfo ShaderModule::getStageCreateInfo()
{
    if(shaderKind == shaderc_vertex_shader) {
        return{
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .stage = VK_SHADER_STAGE_VERTEX_BIT,
            .module = shaderModule,
            .pName = "main"
        };
    } else if(shaderKind == shaderc_fragment_shader) {
        return{
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
            .module = shaderModule,
            .pName = "main"
        };
    } else {
        throw std::runtime_error("Unrecognized shader type");
    }
}
