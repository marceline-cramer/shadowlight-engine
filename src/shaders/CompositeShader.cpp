#include "shaders/CompositeShader.hpp"

CompositeShader::CompositeShader(VkDevice device)
{
    vertShader = new ShaderModule(device, "Composite.vert", shaderc_vertex_shader);
    fragShader = new ShaderModule(device, "Composite.frag", shaderc_fragment_shader);

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

    fragShader->pushCustom(R"""(
layout (input_attachment_index = 0, binding = 0) uniform subpassInput subpassRadiance;

layout(location = 0) out vec4 outColor;

void main() {
    vec3 radiance = max(subpassLoad(subpassRadiance).rgb, vec3(0));

    vec3 color = radiance;
    color = color / (color + vec3(1000.0));
    color = pow(color, vec3(1.0/2.2));  
    outColor = vec4(color, 1.0);
}
    )""");

    vertShader->compile();
    fragShader->compile();
}

CompositeShader::~CompositeShader()
{
    delete vertShader;
    delete fragShader;
}

ShaderStages CompositeShader::getStages()
{
    return{
        vertShader->getStageCreateInfo(),
        fragShader->getStageCreateInfo()
    };
}
