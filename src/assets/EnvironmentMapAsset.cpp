#include "assets/EnvironmentMapAsset.hpp"

void EnvironmentMapAsset::load(Binding* _vk, const char* fileName)
{
    vk = static_cast<VulkanBinding*>(_vk);

    config = vk->fs->loadConfig<EnvironmentMapConfig>(fileName);

    if(config->mapType == ENVIRONMENT_MAP_TYPE_SPHERICAL) {
        vk->texturePool->load(config->sphereMap.data(), cylinderMap);

        textureView = cylinderMap.getAsset()->getImageView();
        textureSampler = cylinderMap.getAsset()->getSampler();
    }
}

void EnvironmentMapAsset::unload()
{
    delete config;
}
