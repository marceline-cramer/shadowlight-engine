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

    VkImageViewCreateInfo viewInfo{
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .image = textureImage,
        .viewType = VK_IMAGE_VIEW_TYPE_2D,
        .format = VK_FORMAT_R8G8B8A8_SRGB,
        .subresourceRange = {
            .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
            .baseMipLevel = 0,
            .levelCount = 1,
            .baseArrayLayer = 0,
            .layerCount = 1
        }
    };

    if(vkCreateImageView(vk->device, &viewInfo, nullptr, &textureView) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create image view");
    }

    VkSamplerCreateInfo samplerInfo{
        .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
        .magFilter = VK_FILTER_LINEAR,
        .minFilter = VK_FILTER_LINEAR,
        .mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
        .addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
        .addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT,
        .addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT,
        .mipLodBias = 0.0f,
        // TODO Anisotropy
        .anisotropyEnable = VK_FALSE,
        .maxAnisotropy = 1.0,
        .compareEnable = VK_FALSE,
        .compareOp = VK_COMPARE_OP_ALWAYS,
        .minLod = 0.0f,
        .maxLod = 0.0f,
        .borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK,
        .unnormalizedCoordinates = VK_FALSE
    };

    if(vkCreateSampler(vk->device, &samplerInfo, nullptr, &textureSampler) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create texture sampler");
    }
}

void TextureAsset::unload()
{
    vkDestroySampler(vk->device, textureSampler, nullptr);
    vkDestroyImageView(vk->device, textureView, nullptr);
    vkDestroyImage(vk->device, textureImage, nullptr);
    vkFreeMemory(vk->device, textureMemory, nullptr);
}
