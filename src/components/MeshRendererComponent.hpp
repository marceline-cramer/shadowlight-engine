#pragma once

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
    
    AssetHandle<MeshAsset> mesh;
    AssetHandle<MaterialAsset> material;
};
