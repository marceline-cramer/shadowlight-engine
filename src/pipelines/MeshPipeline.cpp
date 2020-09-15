#include "pipelines/MeshPipeline.hpp"

MeshPipeline::MeshPipeline(VulkanBinding* _vk)
{
    vk = _vk;

    meshPool = new AssetPool<MeshAsset>(vk);
    materialPool = new AssetPool<MaterialAsset>(vk);
}

MeshPipeline::~MeshPipeline()
{
    delete meshPool;
    delete materialPool;
}

void MeshPipeline::render(VkCommandBuffer commandBuffer)
{
    for(auto c : rendererComponents) {
        c->render(commandBuffer);
    }
}

MeshRendererComponent* MeshPipeline::createMeshRenderer(const char* meshName, const char* materialName)
{
    AssetHandle<MeshAsset> meshAsset;
    meshPool->load(meshName, meshAsset);

    AssetHandle<MaterialAsset> materialAsset;
    materialPool->load(materialName, materialAsset);
    
    auto c = new MeshRendererComponent(this, meshAsset, materialAsset);
    return c;
}
