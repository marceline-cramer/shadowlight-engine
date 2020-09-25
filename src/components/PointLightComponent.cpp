#include "components/PointLightComponent.hpp"

PointLightComponent::PointLightComponent(VulkanBinding* _vk, PointLightSet* _parentSet, VkPipelineLayout _pipelineLayout, VkDescriptorSetLayout _descriptorSetLayout)
{
    vk = _vk;
    parentSet = _parentSet;
    pipelineLayout = _pipelineLayout;
    descriptorSetLayout = _descriptorSetLayout;

    createDescriptorPool();
    createUniform();
    createDescriptorSet();
    writeDescriptorSet();

    parentSet->insert(this);
}

PointLightComponent::~PointLightComponent()
{
    vkDestroyBuffer(vk->device, uniformBuffer, nullptr);
    vkFreeMemory(vk->device, uniformBufferMemory, nullptr);
    vkDestroyDescriptorPool(vk->device, descriptorPool, nullptr);

    parentSet->erase(this);
}

void PointLightComponent::update(double)
{

}

void PointLightComponent::finalize(ComponentSet&, EntityTransform& _transform)
{
    transform = &_transform;
}

void PointLightComponent::render(VkCommandBuffer commandBuffer, CameraComponent* camera)
{
    // TODO Shadow mapping
    // TODO Light volumes
    PointLightUniform ubo{};
    ubo.position = glm::vec3(4.0, -4.0, 4.0);
    ubo.flux = glm::vec3(1.0, 1.0, 1.0);
    ubo.cameraPosition = camera->getPosition();

    void* data;
    vkMapMemory(vk->device, uniformBufferMemory, 0, sizeof(ubo), 0, &data);
        memcpy(data, &ubo, sizeof(ubo));
    vkUnmapMemory(vk->device, uniformBufferMemory);

    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 1, 1, &descriptorSet, 0, nullptr);
    vkCmdDraw(commandBuffer, 4, 1, 0, 0);
}

void PointLightComponent::createDescriptorPool()
{
    std::vector<VkDescriptorPoolSize> poolSizes;

    poolSizes.push_back({
        .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .descriptorCount = 1
    });

    VkDescriptorPoolCreateInfo poolInfo{
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        .maxSets = 1,
        .poolSizeCount = static_cast<uint32_t>(poolSizes.size()),
        .pPoolSizes = poolSizes.data()
    };

    if(vkCreateDescriptorPool(vk->device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create descriptor pool");
    }
}

void PointLightComponent::createUniform()
{
    VkDeviceSize uniformBufferSize = sizeof(PointLightUniform);
    vk->createBuffer(uniformBufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffer, uniformBufferMemory);
}

void PointLightComponent::createDescriptorSet()
{
    VkDescriptorSetAllocateInfo allocInfo{
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool = descriptorPool,
        .descriptorSetCount = 1,
        .pSetLayouts = &descriptorSetLayout
    };

    if(vkAllocateDescriptorSets(vk->device, &allocInfo, &descriptorSet) != VK_SUCCESS) {
        throw std::runtime_error("Failed to allocate descriptor sets");
    }
}

void PointLightComponent::writeDescriptorSet()
{
    std::vector<VkWriteDescriptorSet> descriptorWrites;
    
    VkDescriptorBufferInfo bufferInfo{
        .buffer = uniformBuffer,
        .offset = 0,
        .range = sizeof(PointLightUniform)
    };

    descriptorWrites.push_back({
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .dstSet = descriptorSet,
        .dstBinding = 0,
        .dstArrayElement = 0,
        .descriptorCount = 1,
        .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .pBufferInfo = &bufferInfo
    });

    vkUpdateDescriptorSets(vk->device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
}
