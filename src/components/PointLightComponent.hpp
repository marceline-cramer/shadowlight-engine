#pragma once

#include <set>

#include "bindings/VulkanBinding.hpp"

#include "components/RendererComponent.hpp"

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

    PointLightComponent(VulkanBinding*, PointLightSet*, VkPipelineLayout, VkDescriptorSetLayout);
    ~PointLightComponent();

    virtual void update(double);
    virtual void finalize(ComponentSet&, EntityTransform&);
    virtual void render(VkCommandBuffer, CameraComponent*);
private:
    void createDescriptorPool();
    void createUniform();
    void createDescriptorSet();
    void writeDescriptorSet();

    VulkanBinding* vk;
    PointLightSet* parentSet;
    EntityTransform* transform;

    VkPipelineLayout pipelineLayout;
    VkDescriptorSetLayout descriptorSetLayout;
    VkDescriptorPool descriptorPool;
    VkDescriptorSet descriptorSet;
    VkBuffer uniformBuffer;
    VkDeviceMemory uniformBufferMemory;
};
