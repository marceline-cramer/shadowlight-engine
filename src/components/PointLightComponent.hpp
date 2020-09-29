#pragma once

#include <set>

#include "bindings/VulkanBinding.hpp"

#include "components/RendererComponent.hpp"

#include "config/PointLightConfig.hpp"

class PointLightComponent;
using PointLightSet = std::set<PointLightComponent*>;

struct PointLightUniform
{
    alignas(16) glm::vec3 position;
    alignas(16) glm::vec3 flux;
    alignas(16) glm::vec3 cameraPosition;
};

class PointLightComponent : public RendererComponent
{
public:
    COMPONENT_TYPE("PointLight");

    PointLightComponent(VulkanBinding*, PointLightSet*, VkPipelineLayout, VkDescriptorSetLayout, PointLightConfig&);
    ~PointLightComponent();

    virtual void update(EntityTransform, double);
    virtual void finalize(ComponentSet&) {};
    virtual void createBindings(lua_State*) {};

    virtual void render(VkCommandBuffer, CameraComponent*);
private:
    void createDescriptorPool();
    void createUniform();
    void createDescriptorSet();
    void writeDescriptorSet();

    VulkanBinding* vk;
    PointLightSet* parentSet;

    VkPipelineLayout pipelineLayout;
    VkDescriptorSetLayout descriptorSetLayout;
    VkDescriptorPool descriptorPool;
    VkDescriptorSet descriptorSet;
    VkBuffer uniformBuffer;
    VkDeviceMemory uniformBufferMemory;

    glm::vec3 position;
    glm::vec3 flux;
};
