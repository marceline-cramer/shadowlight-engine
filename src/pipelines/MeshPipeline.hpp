#pragma once

#include "assets/AssetPool.hpp"
#include "assets/MaterialAsset.hpp"

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
    AssetPool<MaterialAsset>* materialPool;
};
