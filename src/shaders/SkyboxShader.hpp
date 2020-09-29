#pragma once

#include "bindings/vk/VulkanInstance.hpp"

#include "shaders/ShaderModule.hpp"

struct SkyboxUniform {
    glm::mat4 view;
    glm::mat4 projection;
};

class SkyboxShader
{
public:
    SkyboxShader(VulkanInstance*);
    ~SkyboxShader();

    ShaderStages getStages();
    VkDescriptorSetLayout getSetLayout() { return setLayout; }
    VkPipelineLayout getPipelineLayout() { return pipelineLayout; }
    VulkanInstance* getInstance() { return vki; }
private:
    void createSetLayout();
    void createPipelineLayout();

    VulkanInstance* vki;

    ShaderModule* vertShader;
    ShaderModule* fragShader;

    VkDescriptorSetLayout setLayout;
    VkPipelineLayout pipelineLayout;
};
