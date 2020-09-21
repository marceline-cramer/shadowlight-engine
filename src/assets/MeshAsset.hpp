#pragma once

#include <sstream>
#include <vector>
#include <array>
#include <unordered_map>

#include <vulkan/vulkan.h>
#include <tiny_obj_loader.h>

#include "assets/Asset.hpp"

#include "bindings/VulkanBinding.hpp"

struct MeshVertex
{
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 texCoord;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{
            .binding = 0,
            .stride = sizeof(MeshVertex),
            .inputRate = VK_VERTEX_INPUT_RATE_VERTEX
        };

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions;

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

        attributeDescriptions[2] = {
            .location = 2,
            .binding = 0,
            .format = VK_FORMAT_R32G32_SFLOAT,
            .offset = offsetof(MeshVertex, texCoord)
        };

        return attributeDescriptions;
    }

    bool operator==(const MeshVertex& other) const {
        return pos == other.pos && color == other.color && texCoord == other.texCoord;
    }
};

namespace std {
    template<> struct hash<MeshVertex> {
        size_t operator()(MeshVertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.pos) ^
                   (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^
                   (hash<glm::vec2>()(vertex.texCoord) << 1);
        }
    };
}

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
    void loadModel(const char*);
    void createVertexBuffer();
    void createIndexBuffer();

    VulkanBinding* vk;

    std::vector<MeshVertex> vertices;
    std::vector<uint32_t> indices;

    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
};
