#include "shaders/SkyboxShader.hpp"

SkyboxShader::SkyboxShader(VkDevice _device)
{
    device = _device;

    vertShader = new ShaderModule(device, "Composite.vert", shaderc_vertex_shader);
    fragShader = new ShaderModule(device, "Composite.frag", shaderc_fragment_shader);

    vertShader->pushCustom(R"""(
vec3 positions[4] = vec3[](
    vec3( 1.0, -1.0, -1.0),
    vec3(-1.0, -1.0, -1.0),
    vec3( 1.0,  1.0, -1.0),
    vec3(-1.0,  1.0, -1.0)
);

void main() {
    gl_Position = vec4(positions[gl_VertexIndex].xy, 0.0, 1.0);
}
    )""");

    fragShader->pushCustom(R"""(
layout(location = 0) out vec4 outColor;

void main() {
    outColor = vec4(100.0, 0.0, 0.0, 1.0);
}
    )""");

    vertShader->compile();
    fragShader->compile();

    createSetLayout();
    createPipelineLayout();
}

SkyboxShader::~SkyboxShader()
{
    vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
    vkDestroyDescriptorSetLayout(device, setLayout, nullptr);

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

    if(vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &setLayout) != VK_SUCCESS) {
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

    if(vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create skybox pipeline layout");
    }
}
