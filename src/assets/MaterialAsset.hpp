#pragma once

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
    // Vulkan objects
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;

    // Bindings
    VulkanBinding* vk;
};
