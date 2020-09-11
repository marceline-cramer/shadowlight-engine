#include "assets/MeshAsset.hpp"

void MeshAsset::load(Binding* _vk, const char* fileName)
{
    vk = static_cast<VulkanBinding*>(_vk);

    // Create staging buffer
    VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    vk->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    // Fill staging buffer
    void* data;
    vkMapMemory(vk->device, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertices.data(), (size_t) bufferSize);
    vkUnmapMemory(vk->device, stagingBufferMemory);

    // Create and copy vertex buffer
    vk->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

    vk->copyBuffer(stagingBuffer, vertexBuffer, bufferSize);

    vkDestroyBuffer(vk->device, stagingBuffer, nullptr);
    vkFreeMemory(vk->device, stagingBufferMemory, nullptr);
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
