#pragma once

#include "assets/AssetHandle.hpp"
#include "assets/EnvironmentMapAsset.hpp"

#include "components/RendererComponent.hpp"

#include "shaders/SkyboxShader.hpp"

class SkyboxComponent;
using SkyboxComponentSet = std::set<SkyboxComponent*>;

class SkyboxComponent : public RendererComponent
{
public:
    COMPONENT_TYPE("Skybox");

    SkyboxComponent(SkyboxComponentSet*, SkyboxShader*, AssetHandle<EnvironmentMapAsset>&);
    ~SkyboxComponent();

    virtual void update(EntityTransform, double) {};
    virtual void finalize(ComponentSet&) {};
    virtual void createBindings(lua_State*) {};

    virtual void render(VkCommandBuffer, CameraComponent*);
private:
    void createDescriptorPool();
    void createDescriptorSet();
    void writeDescriptorSet();

    SkyboxComponentSet* parentSet;
    SkyboxShader* shader;
    AssetHandle<EnvironmentMapAsset> environmentMap;

    VkDescriptorPool descriptorPool;
    VkBuffer uniformBuffer;
    VkDeviceMemory uniformBufferMemory;
    VkDescriptorSet descriptorSet;
};
