#pragma once

#include "assets/Asset.hpp"
#include "assets/TextureAsset.hpp"

#include "bindings/VulkanBinding.hpp"

#include "config/EnvironmentMapConfig.hpp"

class EnvironmentMapAsset : public Asset
{
public:
    virtual void load(Binding*, const char*);
    virtual void unload();

    VkImageView getImageView() { return textureView; }
    VkSampler getSampler() { return textureSampler; }
private:
    VulkanBinding* vk;

    EnvironmentMapConfig* config;

    AssetHandle<TextureAsset> cylinderMap;

    VkImageView textureView;
    VkSampler textureSampler;
};
