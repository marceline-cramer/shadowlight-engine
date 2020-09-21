#include "assets/MeshAsset.hpp"

void MeshAsset::load(Binding* _vk, const char* fileName)
{
    vk = static_cast<VulkanBinding*>(_vk);

    loadModel(fileName);
    createVertexBuffer();
    createIndexBuffer();
}

void MeshAsset::loadModel(const char* fileName)
{
    // Create file stream
    std::string objContents;
    vk->fs->loadFile(fileName, objContents);
    std::istringstream objStream(objContents);

    // Load OBJ file
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, &objStream)) {
        throw std::runtime_error(warn + err);
    }

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            MeshVertex vertex{
                .pos = {
                    attrib.vertices[3*index.vertex_index+0],
                    attrib.vertices[3*index.vertex_index+1],
                    attrib.vertices[3*index.vertex_index+2]
                },
                .color = {
                   1.0, 1.0, 1.0
                },
                .texCoord = {
                    attrib.texcoords[2*index.texcoord_index+0],
                    1.0 - attrib.texcoords[2*index.texcoord_index+1]
                }
            };

            vertices.push_back(vertex);
            indices.push_back(indices.size());
        }
    }
}

void MeshAsset::createVertexBuffer()
{
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

    VkCommandBuffer commandBuffer = vk->beginSingleTimeCommands();
    vk->copyBuffer(commandBuffer, stagingBuffer, vertexBuffer, bufferSize);
    vk->endSingleTimeCommands(commandBuffer);

    vkDestroyBuffer(vk->device, stagingBuffer, nullptr);
    vkFreeMemory(vk->device, stagingBufferMemory, nullptr);
}

void MeshAsset::createIndexBuffer()
{
    // Create staging buffer
    VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    vk->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    // Fill staging buffer
    void* data;
    vkMapMemory(vk->device, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, indices.data(), (size_t) bufferSize);
    vkUnmapMemory(vk->device, stagingBufferMemory);

    // Create and copy index buffer
    vk->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

    VkCommandBuffer commandBuffer = vk->beginSingleTimeCommands();
    vk->copyBuffer(commandBuffer, stagingBuffer, indexBuffer, bufferSize);
    vk->endSingleTimeCommands(commandBuffer);

    vkDestroyBuffer(vk->device, stagingBuffer, nullptr);
    vkFreeMemory(vk->device, stagingBufferMemory, nullptr);
}

void MeshAsset::unload()
{
    vkDestroyBuffer(vk->device, indexBuffer, nullptr);
    vkFreeMemory(vk->device, indexBufferMemory, nullptr);
    vkDestroyBuffer(vk->device, vertexBuffer, nullptr);
    vkFreeMemory(vk->device, vertexBufferMemory, nullptr);
}

void MeshAsset::render(VkCommandBuffer commandBuffer)
{
    VkBuffer vertexBuffers[] = {vertexBuffer};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
    vkCmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT32);
    vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);
}
