#include "shaders/ShaderModule.hpp"

class SkyboxShader
{
public:
    SkyboxShader(VkDevice);
    ~SkyboxShader();

    ShaderStages getStages();
    VkDescriptorSetLayout getSetLayout() { return setLayout; }
    VkPipelineLayout getPipelineLayout() { return pipelineLayout; }
private:
    void createSetLayout();
    void createPipelineLayout();

    VkDevice device;

    ShaderModule* vertShader;
    ShaderModule* fragShader;

    VkDescriptorSetLayout setLayout;
    VkPipelineLayout pipelineLayout;
};
