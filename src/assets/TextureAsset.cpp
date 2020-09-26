#include "assets/TextureAsset.hpp"

void TextureAsset::load(Binding* _vk, const char* fileName)
{
    vk = static_cast<VulkanBinding*>(_vk);

    int texWidth, texHeight, texChannels;

    std::string imageContents;
    vk->fs->loadFile(fileName, imageContents);

    stbi_uc* pixels = stbi_load_from_memory(
        (const stbi_uc*) imageContents.data(),
        imageContents.size(),
        &texWidth, &texHeight,
        &texChannels, STBI_rgb_alpha);
    
    if(!pixels) {
        throw std::runtime_error("Failed to load texture image");
    }

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;

    VkDeviceSize imageSize = texWidth * texHeight * 4;

    vk->createBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(vk->device, stagingBufferMemory, 0, imageSize, 0, &data);
    memcpy(data, pixels, static_cast<size_t>(imageSize));
    vkUnmapMemory(vk->device, stagingBufferMemory);

    stbi_image_free(pixels);

    vk->getInstance()->createImage(
        texWidth, texHeight,
        VK_FORMAT_R8G8B8A8_SRGB,
        VK_IMAGE_TILING_OPTIMAL,
        VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        textureImage, textureMemory);

    VkCommandBuffer commandBuffer = vk->beginSingleTimeCommands();
    vk->transitionImageLayout(commandBuffer, textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    vk->copyBufferToImage(commandBuffer, stagingBuffer, textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
    vk->transitionImageLayout(commandBuffer, textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    vk->endSingleTimeCommands(commandBuffer);

    vkDestroyBuffer(vk->device, stagingBuffer, nullptr);
    vkFreeMemory(vk->device, stagingBufferMemory, nullptr);

    vk->getInstance()->createImageView(textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT, textureView);
    vk->getInstance()->createSampler(textureSampler);
}

void TextureAsset::unload()
{
    vkDestroySampler(vk->device, textureSampler, nullptr);
    vkDestroyImageView(vk->device, textureView, nullptr);
    vkDestroyImage(vk->device, textureImage, nullptr);
    vkFreeMemory(vk->device, textureMemory, nullptr);
}
