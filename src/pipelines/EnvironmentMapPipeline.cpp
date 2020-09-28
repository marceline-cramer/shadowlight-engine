#include "pipelines/EnvironmentMapPipeline.hpp"

EnvironmentMapPipeline::EnvironmentMapPipeline(VulkanBinding* _vk)
{
    vk = _vk;

    environmentMapPool = new AssetPool<EnvironmentMapAsset>(vk);

    skybox = nullptr;
}

EnvironmentMapPipeline::~EnvironmentMapPipeline()
{
    if(skybox) delete skybox;

    delete environmentMapPool;
}

void EnvironmentMapPipeline::render(VkCommandBuffer, CameraComponent*)
{

}

void EnvironmentMapPipeline::setSkybox(const char* skyboxName)
{
    if(skybox) delete skybox;
    skybox = new AssetHandle<EnvironmentMapAsset>;

    environmentMapPool->load(skyboxName, *skybox);
}

void EnvironmentMapPipeline::clearSkybox()
{
    if(skybox) {
        delete skybox;
        skybox = nullptr;
    }
}
