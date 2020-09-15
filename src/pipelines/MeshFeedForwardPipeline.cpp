#include "pipelines/MeshFeedForwardPipeline.hpp"

MeshFeedForwardPipeline::MeshFeedForwardPipeline(VulkanBinding* _vk, Filesystem* _fs)
{
    vk = _vk;
    fs = _fs;

    // Create asset pools
    meshPool = new AssetPool<MeshAsset>(vk);
    materialPool = new AssetPool<MaterialAsset>(vk);

    // TODO Create MeshRendererComponent
    tempMesh = new AssetHandle<MeshAsset>();
    meshPool->load("", *tempMesh);
}

MeshFeedForwardPipeline::~MeshFeedForwardPipeline()
{
    delete tempMesh;

    delete meshPool;
    delete materialPool;
}

void MeshFeedForwardPipeline::render(VkCommandBuffer commandBuffer, VkFramebuffer framebuffer)
{
    VkClearValue clearColor = {0.2f, 0.0f, 0.0f, 1.0f};

    VkRenderPassBeginInfo renderPassInfo{
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
        .renderPass = vk->mainRenderPass,
        .framebuffer = framebuffer,
        .renderArea = {
            .offset = {0, 0},
            .extent = vk->swapChainExtent
        },
        .clearValueCount = 1,
        .pClearValues = &clearColor
    };

    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    // TODO MeshRendererComponent
    //vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
    //tempMesh->getAsset()->render(commandBuffer);

    vkCmdEndRenderPass(commandBuffer);
}
