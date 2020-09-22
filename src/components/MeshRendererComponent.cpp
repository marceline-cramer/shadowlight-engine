#include "components/MeshRendererComponent.hpp"

MeshRendererComponent::MeshRendererComponent(Pipeline* _pipeline, AssetHandle<MeshAsset>& _mesh, AssetHandle<MaterialAsset>& _material, std::vector<AssetHandle<TextureAsset>>& _textures)
{
    pipeline = _pipeline;
    mesh = _mesh;
    material = _material;
    textures = _textures;
    vk = pipeline->vk;
    pipeline->rendererComponents.insert(this);

    VkDeviceSize uniformBufferSize = sizeof(MeshRendererUniform);
    vk->createBuffer(uniformBufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffer, uniformBufferMemory);

    std::vector<VkDescriptorPoolSize> poolSizes;
    poolSizes.push_back({
        .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .descriptorCount = 1
    });

    for(int i = 0; i < textures.size(); i++) {
        poolSizes.push_back({
            .type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
            .descriptorCount = 1
        });
    }

    VkDescriptorPoolCreateInfo poolInfo{
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        .maxSets = 1,
        .poolSizeCount = static_cast<uint32_t>(poolSizes.size()),
        .pPoolSizes = poolSizes.data()
    };

    if(vkCreateDescriptorPool(vk->device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create descriptor pool");
    }

    VkDescriptorSetAllocateInfo allocInfo{
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool = descriptorPool,
        .descriptorSetCount = 1,
        .pSetLayouts = &material.getAsset()->descriptorSetLayout
    };

    if(vkAllocateDescriptorSets(vk->device, &allocInfo, &descriptorSet) != VK_SUCCESS) {
        throw std::runtime_error("Failed to allocate descriptor sets");
    }

    std::vector<VkWriteDescriptorSet> descriptorWrites;

    VkDescriptorBufferInfo bufferInfo{
        .buffer = uniformBuffer,
        .offset = 0,
        .range = sizeof(MeshRendererUniform)
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

    std::vector<VkDescriptorImageInfo> imageInfo;

    for(int i = 0; i < textures.size(); i++) {
        imageInfo.push_back({
            .sampler = textures[i].getAsset()->getSampler(),
            .imageView = textures[i].getAsset()->getImageView(),
            .imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
        });
    }

    for(int i = 0; i < imageInfo.size(); i++) {
        descriptorWrites.push_back({
            .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
            .dstSet = descriptorSet,
            .dstBinding = 1,
            .dstArrayElement = 0,
            .descriptorCount = 1,
            .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
            .pImageInfo = &imageInfo[i]
        });
    }

    vkUpdateDescriptorSets(vk->device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
}

MeshRendererComponent::~MeshRendererComponent()
{
    vkDestroyBuffer(vk->device, uniformBuffer, nullptr);
    vkFreeMemory(vk->device, uniformBufferMemory, nullptr);

    vkDestroyDescriptorPool(vk->device, descriptorPool, nullptr);

    pipeline->rendererComponents.erase(this);
}

void MeshRendererComponent::render(VkCommandBuffer commandBuffer)
{
    MeshRendererUniform ubo{};
    ubo.model = glm::translate(glm::mat4(1.0), transform->position) * glm::mat4(transform->orientation);

    // TODO CameraComponent
    ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.proj = glm::perspective(glm::radians(45.0f), vk->swapChainExtent.width / (float) vk->swapChainExtent.height, 0.1f, 10.0f);
    ubo.proj[1][1] *= -1;

    void* data;
    vkMapMemory(vk->device, uniformBufferMemory, 0, sizeof(ubo), 0, &data);
        memcpy(data, &ubo, sizeof(ubo));
    vkUnmapMemory(vk->device, uniformBufferMemory);

    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, material.getAsset()->pipelineLayout, 0, 1, &descriptorSet, 0, nullptr);
    material.getAsset()->bindPipeline(commandBuffer);
    mesh.getAsset()->render(commandBuffer);
}

void MeshRendererComponent::finalize(ComponentSet& components, EntityTransform& _transform)
{
    transform = &_transform;
}
