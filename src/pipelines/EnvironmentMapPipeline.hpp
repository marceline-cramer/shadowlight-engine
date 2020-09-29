#pragma once

#include "assets/AssetHandle.hpp"
#include "assets/AssetPool.hpp"
#include "assets/EnvironmentMapAsset.hpp"

#include "bindings/VulkanBinding.hpp"

#include "components/SkyboxComponent.hpp"

#include "global/Geometry.hpp"

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
    void createSkyboxSphere();
    void createSkyboxPipeline();

    GBuffer* gBuffer;
    VkPipeline skyboxGraphicsPipeline;

    Geometry::GenericGeometry sphereGeometry;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

    AssetPool<EnvironmentMapAsset>* environmentMapPool;

    SkyboxComponentSet skyboxSet;

    SkyboxShader* skyboxShader;
};
