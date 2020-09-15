#pragma once

#include <array>

#include <glm/glm.hpp>

#include "bindings/VulkanBinding.hpp"

#include "assets/AssetPool.hpp"
#include "assets/MeshAsset.hpp"

#include "global/Filesystem.hpp"

#include "pipelines/MeshPipeline.hpp"

#include "assets/MeshAsset.hpp"

class MeshFeedForwardPipeline : public MeshPipeline
{
public:
    MeshFeedForwardPipeline(VulkanBinding*, Filesystem*);
    ~MeshFeedForwardPipeline();

    virtual void render(VkCommandBuffer, VkFramebuffer);
private:
    // Vulkan objects
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;

    // Mesh pool
    AssetPool<MeshAsset>* meshPool;

    // Bindings
    VulkanBinding* vk;
    Filesystem* fs;

    // TODO Create MeshRendererComponent
    AssetHandle<MeshAsset>* tempMesh;
};
