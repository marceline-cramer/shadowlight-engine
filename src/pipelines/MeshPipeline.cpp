#include "pipelines/MeshPipeline.hpp"

MeshPipeline::MeshPipeline(VulkanBinding* _vk)
{
    vk = _vk;

    meshPool = new AssetPool<MeshAsset>(vk);
    materialPool = new AssetPool<MaterialAsset>(vk);
    texturePool = new AssetPool<TextureAsset>(vk);
}

MeshPipeline::~MeshPipeline()
{
    delete meshPool;
    delete materialPool;
    delete texturePool;
}

void MeshPipeline::render(VkCommandBuffer commandBuffer)
{
    for(auto c : rendererComponents) {
        c->render(commandBuffer);
    }
}

MeshRendererComponent* MeshPipeline::createMeshRenderer(const char* meshName, const char* materialName, const char* textureName)
{
    AssetHandle<MeshAsset> meshAsset;
    meshPool->load(meshName, meshAsset);

    AssetHandle<MaterialAsset> materialAsset;
    materialPool->load(materialName, materialAsset);

    AssetHandle<TextureAsset> textureAsset;
    texturePool->load(textureName, textureAsset);
    
    auto c = new MeshRendererComponent(this, meshAsset, materialAsset, textureAsset);
    return c;
}
