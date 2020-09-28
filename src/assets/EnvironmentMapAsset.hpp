#pragma once

#include "assets/Asset.hpp"
#include "assets/TextureAsset.hpp"

class EnvironmentMapAsset : public Asset
{
public:
    virtual void load(Binding*, const char*);
    virtual void unload();

    VkImageView getImageView() { return textureView; }
    VkSampler getSampler() { return textureSampler; }
private:
    VkImageView textureView;
    VkSampler textureSampler;
};
