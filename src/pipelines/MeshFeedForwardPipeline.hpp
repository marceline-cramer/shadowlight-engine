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
    // Bindings
    VulkanBinding* vk;
    Filesystem* fs;
};
