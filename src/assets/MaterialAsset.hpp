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

    std::vector<std::string> getTextures() { return textures; }
    VkDescriptorSetLayout getSetLayout() { return descriptorSetLayout; };
    VkPipelineLayout getPipelineLayout() { return pipelineLayout; }
private:
    // Utility functions
    void createSetLayout();
    void createPipelineLayout();
    void createPipeline(const char*, const char*);
    VkShaderModule compileShader(const char*, std::string, shaderc_shader_kind);
    
    // Vulkan objects
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;

    // Bindings
    VulkanBinding* vk;

    // Material info
    std::vector<std::string> textures;
};
