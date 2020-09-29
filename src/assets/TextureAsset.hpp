#pragma once

#include "stb_image.h"

#include "assets/Asset.hpp"

#include "bindings/vk/VulkanInstance.hpp"

class TextureAsset : public Asset
{
public:
    virtual void load(Binding*, const char*);
    virtual void unload();

    VkImageView getImageView() { return textureView; }
    VkSampler getSampler() { return textureSampler; }
private:
    VulkanInstance* vki;

    VkFormat textureFormat;
    VkImage textureImage;
    VkDeviceMemory textureMemory;
    VkImageView textureView;
    VkSampler textureSampler;
};
