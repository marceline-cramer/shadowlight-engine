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

    VkImageCreateInfo imageInfo{
        .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .flags = 0,
        .imageType = VK_IMAGE_TYPE_2D,
        .format = VK_FORMAT_R8G8B8A8_SRGB,
        .extent = {
            .width = static_cast<uint32_t>(texWidth),
            .height = static_cast<uint32_t>(texHeight),
            .depth = 1
        },
        .mipLevels = 1,
        .arrayLayers = 1,
        .samples = VK_SAMPLE_COUNT_1_BIT,
        .tiling = VK_IMAGE_TILING_OPTIMAL,
        .usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED
    };

    if(vkCreateImage(vk->device, &imageInfo, nullptr, &textureImage) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create image");
    }

    VkMemoryRequirements memRequirements;
    vkGetImageMemoryRequirements(vk->device, textureImage, &memRequirements);

    VkMemoryAllocateInfo allocInfo{
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .allocationSize = memRequirements.size,
        .memoryTypeIndex = vk->findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
    };

    if(vkAllocateMemory(vk->device, &allocInfo, nullptr, &textureMemory) != VK_SUCCESS) {
        throw std::runtime_error("Failed to allocate image memory");
    }

    vkBindImageMemory(vk->device, textureImage, textureMemory, 0);

    VkCommandBuffer commandBuffer = vk->beginSingleTimeCommands();
    vk->transitionImageLayout(commandBuffer, textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    vk->copyBufferToImage(commandBuffer, stagingBuffer, textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
    vk->transitionImageLayout(commandBuffer, textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    vk->endSingleTimeCommands(commandBuffer);

    vkDestroyBuffer(vk->device, stagingBuffer, nullptr);
    vkFreeMemory(vk->device, stagingBufferMemory, nullptr);
}

void TextureAsset::unload()
{
    vkDestroyImage(vk->device, textureImage, nullptr);
    vkFreeMemory(vk->device, textureMemory, nullptr);
}
