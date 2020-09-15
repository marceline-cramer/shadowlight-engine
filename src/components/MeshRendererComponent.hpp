#pragma once

#include <chrono>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "assets/AssetHandle.hpp"
#include "assets/MeshAsset.hpp"
#include "assets/MaterialAsset.hpp"

#include "components/RendererComponent.hpp"

class MeshRendererComponent : public RendererComponent
{
public:
    COMPONENT_TYPE("MeshRenderer");

    MeshRendererComponent(Pipeline*, AssetHandle<MeshAsset>&, AssetHandle<MaterialAsset>&);
    ~MeshRendererComponent();

    void render(VkCommandBuffer);
private:
    Pipeline* pipeline;
    VulkanBinding* vk;

    VkBuffer uniformBuffer;
    VkDeviceMemory uniformBufferMemory;
    VkDescriptorPool descriptorPool;
    VkDescriptorSet descriptorSet;
    
    AssetHandle<MeshAsset> mesh;
    AssetHandle<MaterialAsset> material;
};
