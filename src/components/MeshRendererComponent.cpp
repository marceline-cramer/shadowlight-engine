#include "components/MeshRendererComponent.hpp"

MeshRendererComponent::MeshRendererComponent(Pipeline* _pipeline, AssetHandle<MeshAsset>& _mesh, AssetHandle<MaterialAsset>& _material)
{
    pipeline = _pipeline;
    mesh = _mesh;
    material = _material;

    pipeline->rendererComponents.insert(this);
}

MeshRendererComponent::~MeshRendererComponent()
{
    pipeline->rendererComponents.erase(this);
}

void MeshRendererComponent::render(VkCommandBuffer commandBuffer)
{
    material.getAsset()->bindPipeline(commandBuffer);
    mesh.getAsset()->render(commandBuffer);
}
