#include "shaders/MaterialShader.hpp"

MaterialShader::MaterialShader(VkDevice device, std::vector<std::string> textures, std::string materialCode)
{
    vertShader = new ShaderModule(device, "Material.vert", shaderc_vertex_shader);
    fragShader = new ShaderModule(device, "Material.frag", shaderc_fragment_shader);

    vertShader->pushCustom(R"""(
layout(set = 0, binding = 0) uniform UniformBufferObject {
    mat4 model, view, proj;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inNormal;

layout(location = 0) out vec3 fragPosition;
layout(location = 1) out vec3 fragColor;
layout(location = 2) out vec2 fragTexCoord;
layout(location = 3) out vec3 fragNormal;

void main() {
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
    fragPosition = (ubo.model * vec4(inPosition, 1.0)).xyz;
    fragColor = inColor;
    fragTexCoord = inTexCoord;
    fragNormal = (ubo.model * vec4(inNormal, 0.0)).xyz;
}
    )""");

    for(uint32_t i = 0; i < textures.size(); i++) {
        std::ostringstream textureBinding;
        textureBinding << "layout(binding = 1) uniform sampler2D ";
        textureBinding << textures[i];
        textureBinding << "Sampler;";
        fragShader->pushCustom(textureBinding.str());
    }

    fragShader->pushCustom(R"""(
layout(location = 0) in vec3 fragPosition;
layout(location = 1) in vec3 fragColor;
layout(location = 2) in vec2 fragTexCoord;
layout(location = 3) in vec3 fragNormal;

layout(location = 0) out vec3 outAlbedo;
layout(location = 1) out vec3 outPosition;
layout(location = 2) out vec3 outNormal;
layout(location = 3) out vec4 outProperties;

void shadeMaterial(out vec3, out vec2, out float, out float);

void main() {
    float metallic;
    float roughness;
    vec2 normalDisplace;

    shadeMaterial(outAlbedo, normalDisplace, metallic, roughness);

    outPosition = fragPosition;
    outNormal = fragNormal;
    outProperties = vec4(metallic, roughness, 0.0, 0.0);
}
    )""");

    fragShader->pushCustom(materialCode);

    vertShader->compile();
    fragShader->compile();
}

MaterialShader::~MaterialShader()
{
    delete vertShader;
    delete fragShader;
}

ShaderStages MaterialShader::getStages()
{
    return{
        vertShader->getStageCreateInfo(),
        fragShader->getStageCreateInfo()
    };
}
