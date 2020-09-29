#pragma once

#include "assets/AssetHandle.hpp"
#include "assets/AssetPool.hpp"
#include "assets/EnvironmentMapAsset.hpp"

#include "bindings/VulkanBinding.hpp"

#include "components/SkyboxComponent.hpp"

#include "pipelines/Pipeline.hpp"

#include "shaders/SkyboxShader.hpp"

class EnvironmentMapPipeline : public Pipeline
{
public:
    EnvironmentMapPipeline(VulkanBinding*);
    ~EnvironmentMapPipeline();

    virtual void render(VkCommandBuffer, CameraComponent*);

    SkyboxComponent* createSkybox(const char*);
private:
    void createSkyboxPipeline();

    GBuffer* gBuffer;
    VkPipeline skyboxGraphicsPipeline;

    AssetPool<EnvironmentMapAsset>* environmentMapPool;

    SkyboxComponentSet skyboxSet;

    SkyboxShader* skyboxShader;
};
