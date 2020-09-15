#pragma once

#include <vector>
#include <array>

#include <vulkan/vulkan.h>

#include "assets/Asset.hpp"

#include "bindings/VulkanBinding.hpp"

struct MeshVertex
{
    glm::vec3 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{
            .binding = 0,
            .stride = sizeof(MeshVertex),
            .inputRate = VK_VERTEX_INPUT_RATE_VERTEX
        };

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions;

        attributeDescriptions[0] = {
            .location = 0,
            .binding = 0,
            .format = VK_FORMAT_R32G32B32_SFLOAT,
            .offset = offsetof(MeshVertex, pos)
        };

        attributeDescriptions[1] = {
            .location = 1,
            .binding = 0,
            .format = VK_FORMAT_R32G32B32_SFLOAT,
            .offset = offsetof(MeshVertex, color)
        };

        return attributeDescriptions;
    }
};

struct MeshRendererUniform
{
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

class MeshAsset : public Asset
{
public:
    virtual void load(Binding*, const char*);
    virtual void unload();
    
    void render(VkCommandBuffer);
private:
    VulkanBinding* vk;

    // TODO Load a model
    const std::vector<MeshVertex> vertices = {
        {{0.0f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, 0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}}
    };

    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
};
