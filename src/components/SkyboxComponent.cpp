#include "components/SkyboxComponent.hpp"

SkyboxComponent::SkyboxComponent(SkyboxComponentSet* _parentSet, SkyboxShader* _shader, AssetHandle<EnvironmentMapAsset>& _environmentMap)
{
    parentSet = _parentSet;
    shader = _shader;
    environmentMap = _environmentMap;

    parentSet->insert(this);

    createDescriptorPool();
    createDescriptorSet();
    writeDescriptorSet();
}

SkyboxComponent::~SkyboxComponent()
{
    parentSet->erase(this);

    vkDestroyBuffer(shader->getInstance()->device, uniformBuffer, nullptr);
    vkFreeMemory(shader->getInstance()->device, uniformBufferMemory, nullptr);
    vkDestroyDescriptorPool(shader->getInstance()->device, descriptorPool, nullptr);
}

void SkyboxComponent::render(VkCommandBuffer commandBuffer, CameraComponent* camera)
{
    SkyboxUniform ubo{};
    ubo.view = camera->getViewMatrix();
    ubo.projection = camera->getProjectionMatrix();

    void* data;
    vkMapMemory(shader->getInstance()->device, uniformBufferMemory, 0, sizeof(ubo), 0, &data);
        memcpy(data, &ubo, sizeof(ubo));
    vkUnmapMemory(shader->getInstance()->device, uniformBufferMemory);

    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, shader->getPipelineLayout(), 0, 1, &descriptorSet, 0, nullptr);
    vkCmdDraw(commandBuffer, 4, 1, 0, 0);
}

void SkyboxComponent::createDescriptorPool()
{
    std::vector<VkDescriptorPoolSize> poolSizes;

    poolSizes.push_back({
        .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .descriptorCount = 1
    });

    poolSizes.push_back({
        .type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        .descriptorCount = 1
    });

    VkDescriptorPoolCreateInfo poolInfo{
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        .maxSets = 1,
        .poolSizeCount = static_cast<uint32_t>(poolSizes.size()),
        .pPoolSizes = poolSizes.data()
    };

    if(vkCreateDescriptorPool(shader->getInstance()->device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create descriptor pool");
    }
}

void SkyboxComponent::createDescriptorSet()
{
    auto setLayout = shader->getSetLayout();

    VkDescriptorSetAllocateInfo allocInfo{
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool = descriptorPool,
        .descriptorSetCount = 1,
        .pSetLayouts = &setLayout
    };

    if(vkAllocateDescriptorSets(shader->getInstance()->device, &allocInfo, &descriptorSet) != VK_SUCCESS) {
        throw std::runtime_error("Failed to allocate descriptor set");
    }
}

void SkyboxComponent::writeDescriptorSet()
{
    std::vector<VkWriteDescriptorSet> descriptorWrites;

    VkDeviceSize uniformBufferSize = sizeof(MeshRendererUniform);
    shader->getInstance()->createBuffer(uniformBufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffer, uniformBufferMemory);

    VkDescriptorBufferInfo bufferInfo{
        .buffer = uniformBuffer,
        .offset = 0,
        .range = sizeof(SkyboxUniform)
    };

    VkDescriptorImageInfo imageInfo{
        .sampler = environmentMap.getAsset()->getSampler(),
        .imageView = environmentMap.getAsset()->getImageView(),
        .imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
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

    descriptorWrites.push_back({
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .dstSet = descriptorSet,
        .dstBinding = 1,
        .dstArrayElement = 0,
        .descriptorCount = 1,
        .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        .pImageInfo = &imageInfo
    });

    vkUpdateDescriptorSets(shader->getInstance()->device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
}
