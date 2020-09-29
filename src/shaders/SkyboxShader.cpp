#include "shaders/SkyboxShader.hpp"

SkyboxShader::SkyboxShader(VulkanInstance* _vki)
{
    vki = _vki;

    vertShader = new ShaderModule(vki->device, "Skybox.vert", shaderc_vertex_shader);
    fragShader = new ShaderModule(vki->device, "Skybox.frag", shaderc_fragment_shader);

    vertShader->pushCustom(R"""(
vec3 positions[4] = vec3[](
    vec3( 1.0, -1.0, 1.0),
    vec3(-1.0, -1.0, 1.0),
    vec3( 1.0,  1.0, 1.0),
    vec3(-1.0,  1.0, 1.0)
);

layout(set = 0, binding = 0) uniform UniformBufferObject {
    mat4 view;
    mat4 proj;
} ubo;

layout(location = 0) out vec3 texCoord;

void main() {
    vec3 position = positions[gl_VertexIndex];
    gl_Position = ubo.proj * vec4((ubo.view * vec4(position, 0.0)).xyz, 1.0);
    texCoord = position;
}
    )""");

    fragShader->pushCustom(R"""(
layout(binding = 1) uniform sampler2D environmentMap;

layout(location = 0) in vec3 texCoord;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = texture(environmentMap, texCoord.xy);
}
    )""");

    vertShader->compile();
    fragShader->compile();

    createSetLayout();
    createPipelineLayout();
}

SkyboxShader::~SkyboxShader()
{
    vkDestroyPipelineLayout(vki->device, pipelineLayout, nullptr);
    vkDestroyDescriptorSetLayout(vki->device, setLayout, nullptr);

    delete vertShader;
    delete fragShader;
}

ShaderStages SkyboxShader::getStages()
{
    return{
        vertShader->getStageCreateInfo(),
        fragShader->getStageCreateInfo()
    };
}

void SkyboxShader::createSetLayout()
{
    std::vector<VkDescriptorSetLayoutBinding> layoutBindings;

    layoutBindings.push_back({
        .binding = 0,
        .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .descriptorCount = 1,
        .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
        .pImmutableSamplers = nullptr
    });

    layoutBindings.push_back({
        .binding = 1,
        .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        .descriptorCount = 1,
        .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
        .pImmutableSamplers = nullptr
    });

    VkDescriptorSetLayoutCreateInfo layoutInfo{
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .bindingCount = static_cast<uint32_t>(layoutBindings.size()),
        .pBindings = layoutBindings.data()
    };

    if(vkCreateDescriptorSetLayout(vki->device, &layoutInfo, nullptr, &setLayout) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create skybox descriptor set layout");
    }
}

void SkyboxShader::createPipelineLayout()
{
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .setLayoutCount = 1,
        .pSetLayouts = &setLayout,
        .pushConstantRangeCount = 0,
        .pPushConstantRanges = nullptr
    };

    if(vkCreatePipelineLayout(vki->device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create skybox pipeline layout");
    }
}
