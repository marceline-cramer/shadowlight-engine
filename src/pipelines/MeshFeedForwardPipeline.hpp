#pragma once

#include <array>

#include <glm/glm.hpp>

#include "bindings/VulkanBinding.hpp"

#include "assets/AssetPool.hpp"
#include "assets/MeshAsset.hpp"

#include "global/Filesystem.hpp"

#include "pipelines/MeshPipeline.hpp"

#include "assets/MeshAsset.hpp"
#include "assets/MaterialAsset.hpp"

class MeshFeedForwardPipeline : public MeshPipeline
{
public:
    MeshFeedForwardPipeline(VulkanBinding*, Filesystem*);
    ~MeshFeedForwardPipeline();

    virtual void render(VkCommandBuffer, VkFramebuffer);
private:
    // Asset pools
    AssetPool<MeshAsset>* meshPool;
    AssetPool<MaterialAsset>* materialPool;

    // Bindings
    VulkanBinding* vk;
    Filesystem* fs;

    // TODO Create MeshRendererComponent
    AssetHandle<MeshAsset>* tempMesh;
};
