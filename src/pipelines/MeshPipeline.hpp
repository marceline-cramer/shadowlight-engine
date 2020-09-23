#pragma once

#include "assets/AssetPool.hpp"
#include "assets/MeshAsset.hpp"
#include "assets/MaterialAsset.hpp"
#include "assets/TextureAsset.hpp"

#include "bindings/VulkanBinding.hpp"

#include "components/MeshRendererComponent.hpp"

#include "pipelines/Pipeline.hpp"

class MeshPipeline : public Pipeline
{
public:
    MeshPipeline(VulkanBinding*);
    ~MeshPipeline();

    virtual void render(VkCommandBuffer, CameraComponent*);

    MeshRendererComponent* createMeshRenderer(const char*, const char*, std::map<std::string, const char*>);
private:
    AssetPool<MeshAsset>* meshPool;
    AssetPool<MaterialAsset>* materialPool;
    AssetPool<TextureAsset>* texturePool;
};
