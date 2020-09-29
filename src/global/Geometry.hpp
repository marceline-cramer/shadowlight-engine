#pragma once

#include <vector>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/hash.hpp>

#include <vulkan/vulkan.h>

namespace Geometry {
    struct GeometryVertex {
        glm::vec3 position;
        glm::vec2 texCoord;

        static VkVertexInputBindingDescription getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription{
                .binding = 0,
                .stride = sizeof(GeometryVertex),
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
                .offset = offsetof(GeometryVertex, position)
            };

            attributeDescriptions[1] = {
                .location = 1,
                .binding = 0,
                .format = VK_FORMAT_R32G32_SFLOAT,
                .offset = offsetof(GeometryVertex, texCoord)
            };

            return attributeDescriptions;
        }
    };

    using GeometryIndex = uint32_t;

    struct GenericGeometry {
        std::vector<GeometryVertex> vertices;
        std::vector<GeometryIndex> indices;
    };

    void createUVSphere(int, int, double, GenericGeometry*);
};
