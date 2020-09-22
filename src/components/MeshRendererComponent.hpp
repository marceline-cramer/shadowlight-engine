#pragma once

#include <chrono>

#include "assets/AssetHandle.hpp"
#include "assets/MeshAsset.hpp"
#include "assets/MaterialAsset.hpp"
#include "assets/TextureAsset.hpp"

#include "components/RendererComponent.hpp"

class MeshRendererComponent : public RendererComponent
{
public:
    COMPONENT_TYPE("MeshRenderer");

    MeshRendererComponent(Pipeline*, AssetHandle<MeshAsset>&, AssetHandle<MaterialAsset>&, std::vector<AssetHandle<TextureAsset>>&);
    ~MeshRendererComponent();

    virtual void render(VkCommandBuffer);
    virtual void finalize(ComponentSet&, EntityTransform&);
private:
    Pipeline* pipeline;
    VulkanBinding* vk;

    EntityTransform* transform;

    VkBuffer uniformBuffer;
    VkDeviceMemory uniformBufferMemory;
    VkDescriptorPool descriptorPool;
    VkDescriptorSet descriptorSet;
    
    AssetHandle<MeshAsset> mesh;
    AssetHandle<MaterialAsset> material;
    std::vector<AssetHandle<TextureAsset>> textures;
};
