#include "assets/TextureAsset.hpp"

void TextureAsset::load(Binding* _vki, const char* fileName)
{
    vki = static_cast<VulkanInstance*>(_vki);

    int texWidth, texHeight, texChannels;

    std::vector<char> imageContents;
    vki->fs->loadFile(fileName, imageContents);

    // Load HDR
    void* pixels;
    VkDeviceSize imageSize;

    if(!stbi_is_hdr_from_memory((const stbi_uc*) imageContents.data(), imageContents.size())) {
        pixels = stbi_load_from_memory(
            (const stbi_uc*) imageContents.data(),
            imageContents.size(),
            &texWidth, &texHeight,
            &texChannels, STBI_rgb_alpha);
        textureFormat = VK_FORMAT_R8G8B8A8_SRGB;
        imageSize = texWidth * texHeight * 4;
        
        if(!pixels) {
            throw std::runtime_error("Failed to load texture image");
        }
    } else {
        pixels = stbi_loadf_from_memory(
            (const stbi_uc*) imageContents.data(),
            imageContents.size(),
            &texWidth, &texHeight,
            &texChannels, STBI_rgb_alpha
        );
        textureFormat = VK_FORMAT_R32G32B32A32_SFLOAT;
        imageSize = texWidth * texHeight * 4 * sizeof(float);

        if(!pixels) {
            throw std::runtime_error("Failed to load texture image");
        }
    }

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;

    vki->createBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(vki->device, stagingBufferMemory, 0, imageSize, 0, &data);
    memcpy(data, pixels, static_cast<size_t>(imageSize));
    vkUnmapMemory(vki->device, stagingBufferMemory);

    stbi_image_free(pixels);

    vki->createImage(
        texWidth, texHeight,
        textureFormat,
        VK_IMAGE_TILING_OPTIMAL,
        VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        textureImage, textureMemory);

    VkCommandBuffer commandBuffer = vki->beginSingleTimeCommands();
    vki->transitionImageLayout(commandBuffer, textureImage, textureFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    vki->copyBufferToImage(commandBuffer, stagingBuffer, textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
    vki->transitionImageLayout(commandBuffer, textureImage, textureFormat, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    vki->endSingleTimeCommands(commandBuffer);

    vkDestroyBuffer(vki->device, stagingBuffer, nullptr);
    vkFreeMemory(vki->device, stagingBufferMemory, nullptr);

    vki->createImageView(textureImage, textureFormat, VK_IMAGE_ASPECT_COLOR_BIT, textureView);
    vki->createSampler(textureSampler);
}

void TextureAsset::unload()
{
    vkDestroySampler(vki->device, textureSampler, nullptr);
    vkDestroyImageView(vki->device, textureView, nullptr);
    vkDestroyImage(vki->device, textureImage, nullptr);
    vkFreeMemory(vki->device, textureMemory, nullptr);
}
