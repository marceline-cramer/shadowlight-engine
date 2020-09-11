#include "assets/MeshAsset.hpp"

void MeshAsset::load(Binding* _vk, const char* fileName)
{
    vk = static_cast<VulkanBinding*>(_vk);

    // Create vertex buffer
    VkBufferCreateInfo vertexBufferInfo{
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = sizeof(vertices[0]) * vertices.size(),
        .usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE
    };

    if(vkCreateBuffer(vk->device, &vertexBufferInfo, nullptr, &vertexBuffer) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create vertex buffer");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(vk->device, vertexBuffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .allocationSize = memRequirements.size,
        .memoryTypeIndex = vk->findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT),
    };

    if(vkAllocateMemory(vk->device, &allocInfo, nullptr, &vertexBufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("Failed to allocate vertex buffer memory");
    }

    vkBindBufferMemory(vk->device, vertexBuffer, vertexBufferMemory, 0);

    // Fill vertex buffer
    void* data;
    vkMapMemory(vk->device, vertexBufferMemory, 0, vertexBufferInfo.size, 0, &data);
    memcpy(data, vertices.data(), (size_t) vertexBufferInfo.size);
    vkUnmapMemory(vk->device, vertexBufferMemory);
}

void MeshAsset::unload()
{
    vkDestroyBuffer(vk->device, vertexBuffer, nullptr);
    vkFreeMemory(vk->device, vertexBufferMemory, nullptr);
}

void MeshAsset::render(VkCommandBuffer commandBuffer)
{
    VkBuffer vertexBuffers[] = {vertexBuffer};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
    vkCmdDraw(commandBuffer, static_cast<uint32_t>(vertices.size()), 1, 0, 0);
}
