#include "shaders/PointLightShader.hpp"

PointLightShader::PointLightShader(VulkanInstance* vki)
{
    vertShader = new ShaderModule(vki, "PointLight.vert", shaderc_vertex_shader);
    fragShader = new ShaderModule(vki, "PointLight.frag", shaderc_fragment_shader);

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
layout (set = 1, binding = 0) uniform UniformBufferObject {
    vec3 position;
    vec3 flux;
    vec3 cameraPosition;
} lightProperties;

layout (binding = 0, input_attachment_index = 0) uniform subpassInput subpassAlbedo;
layout (binding = 1, input_attachment_index = 1) uniform subpassInput subpassPosition;
layout (binding = 2, input_attachment_index = 2) uniform subpassInput subpassNormal;
layout (binding = 3, input_attachment_index = 3) uniform subpassInput subpassProperties;

layout(location = 0) out vec3 outRadiance;

const float PI = 3.141592;

float DistributionGGX(float NdotH, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH2 = NdotH*NdotH;
	
    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
	
    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return num / denom;
}

float GeometrySmith(float NdotV, float NdotL, float roughness)
{
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}

vec3 SchlickFresnel(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 shadePointLight(
    vec3 N, vec3 V, vec3 L,
    vec3 flux,
    vec3 albedo, vec3 position, vec3 normal,
    float metallic, float roughness
) {
    // Halfway point
    float attenuation = 1.0/dot(L, L);
    L = normalize(L);
    vec3 H = normalize(V + L);

    // Dot products
    float NdotL = max(dot(N, L), 0.0);
    float NdotV = max(dot(N, V), 0.0);
    float NdotH = max(dot(N, H), 0.0);
    float LdotH = max(dot(L, H), 0.0);

    // Received light
    vec3 received = flux * attenuation * NdotL;

    // Normal distribution
    float NDF = DistributionGGX(NdotH, roughness);

    // Geometric shadowing
    float G = GeometrySmith(NdotV, NdotL, roughness);

    // Fresnel
    vec3 F0 = mix(vec3(0.04), albedo, metallic);
    vec3 F  = SchlickFresnel(LdotH, F0);

    // Combine BRDF
    vec3 specularity = (NDF * F * G) / (4 * (NdotL * NdotV));

    return specularity * received;
}

void main() {
    vec3 albedo = subpassLoad(subpassAlbedo).rgb;
    vec3 position = subpassLoad(subpassPosition).rgb;
    vec3 normal = subpassLoad(subpassNormal).rgb;
    vec4 properties = subpassLoad(subpassProperties);

    float metallic = properties.r;
    float roughness = properties.g;

    vec3 N = normalize(normal);
    vec3 V = normalize(lightProperties.cameraPosition - position);
    vec3 L = lightProperties.position - position;
  
    outRadiance = max(shadePointLight(
        N, V, L,
        lightProperties.flux,
        albedo, position, normal,
        metallic, roughness
    ), vec3(0.0));
}
    )""");

    vertShader->compile();
    fragShader->compile();
}

PointLightShader::~PointLightShader()
{
    delete vertShader;
    delete fragShader;
}

ShaderStages PointLightShader::getStages()
{
    return{
        vertShader->getStageCreateInfo(),
        fragShader->getStageCreateInfo()
    };
}
