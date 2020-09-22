#pragma once

#include "shaderc/shaderc.hpp"

#include "assets/Asset.hpp"
#include "assets/MeshAsset.hpp"

#include "bindings/VulkanBinding.hpp"

class MaterialAsset : public Asset
{
public:
    virtual void load(Binding*, const char*);
    virtual void unload();

    void bindPipeline(VkCommandBuffer);
private:
    // Utility functions
    VkShaderModule compileShader(const char*, std::string, shaderc_shader_kind);

    friend class MeshRendererComponent;
    
    // Vulkan objects
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;

    // Bindings
    VulkanBinding* vk;
};
