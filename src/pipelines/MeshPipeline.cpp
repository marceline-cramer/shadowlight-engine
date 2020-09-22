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

// TODO This is gross
MeshRendererComponent* MeshPipeline::createMeshRenderer(const char* meshName, const char* materialName, std::map<std::string, const char*> textureNames)
{
    AssetHandle<MeshAsset> meshAsset;
    meshPool->load(meshName, meshAsset);

    AssetHandle<MaterialAsset> materialAsset;
    materialPool->load(materialName, materialAsset);

    std::vector<AssetHandle<TextureAsset>> textureAssets;
    auto textureList = materialAsset.getAsset()->getTextures();

    for(auto textureName : textureList) {
        auto textureLookup = textureNames.find(textureName.data());

        if(textureLookup == textureNames.end()) {
            std::ostringstream errorMessage;
            errorMessage << "Missing MaterialAsset texture ";
            errorMessage << textureName;
            throw std::runtime_error(errorMessage.str());
        }

        auto textureFile = textureLookup->second;

        AssetHandle<TextureAsset> textureAsset;
        texturePool->load(textureFile, textureAsset);

        textureAssets.push_back(textureAsset);
    }
    
    auto c = new MeshRendererComponent(this, meshAsset, materialAsset, textureAssets);
    return c;
}
