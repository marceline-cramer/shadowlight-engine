#pragma once

#include "assets/AssetHandle.hpp"
#include "assets/AssetPool.hpp"
#include "assets/EnvironmentMapAsset.hpp"

#include "bindings/VulkanBinding.hpp"

#include "pipelines/Pipeline.hpp"

class EnvironmentMapPipeline : public Pipeline
{
public:
    EnvironmentMapPipeline(VulkanBinding*);
    ~EnvironmentMapPipeline();

    virtual void render(VkCommandBuffer, CameraComponent*);

    void setSkybox(const char*);
    void clearSkybox();
private:
    AssetPool<EnvironmentMapAsset>* environmentMapPool;

    AssetHandle<EnvironmentMapAsset>* skybox;
};
