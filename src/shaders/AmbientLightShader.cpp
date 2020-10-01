#include "shaders/AmbientLightShader.hpp"

AmbientLightShader::AmbientLightShader(VulkanInstance* vki)
{
    vertShader = new ShaderModule(vki, "AmbientLight.vert", shaderc_vertex_shader);
    fragShader = new ShaderModule(vki, "AmbientLight.frag", shaderc_fragment_shader);

    vertShader->pushCustom(R"""(
vec2 positions[4] = vec2[](
    vec2( 1.0, -1.0),
    vec2(-1.0, -1.0),
    vec2( 1.0,  1.0),
    vec2(-1.0,  1.0)
);

void main() {
    gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);
}
    )""");

    // TODO Autogenerate subpass bindings from G-buffer vector
    fragShader->pushCustom(R"""(
layout (binding = 0, input_attachment_index = 0) uniform subpassInput subpassAlbedo;
layout (binding = 1, input_attachment_index = 1) uniform subpassInput subpassPosition;
layout (binding = 2, input_attachment_index = 2) uniform subpassInput subpassNormal;
layout (binding = 3, input_attachment_index = 3) uniform subpassInput subpassProperties;

layout(location = 0) out vec3 outColor;

void main() {
    vec3 albedo = subpassLoad(subpassAlbedo).rgb;
    outColor = albedo * vec3(0.0001);
}
    )""");

    vertShader->compile();
    fragShader->compile();
}

AmbientLightShader::~AmbientLightShader()
{
    delete vertShader;
    delete fragShader;
}

ShaderStages AmbientLightShader::getStages()
{
    return{
        vertShader->getStageCreateInfo(),
        fragShader->getStageCreateInfo()
    };
}
