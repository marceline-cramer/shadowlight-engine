#include "components/MeshRendererComponent.hpp"

MeshRendererComponent::MeshRendererComponent(Pipeline* _pipeline, AssetHandle<MeshAsset>& _mesh, AssetHandle<MaterialAsset>& _material)
{
    pipeline = _pipeline;
    mesh = _mesh;
    material = _material;
    vk = pipeline->vk;
    pipeline->rendererComponents.insert(this);

    VkDeviceSize uniformBufferSize = sizeof(MeshRendererUniform);
    vk->createBuffer(uniformBufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffer, uniformBufferMemory);

    VkDescriptorPoolSize poolSize{
        .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .descriptorCount = 1
    };

    VkDescriptorPoolCreateInfo poolInfo{
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        .maxSets = 1,
        .poolSizeCount = 1,
        .pPoolSizes = &poolSize
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

    VkDescriptorBufferInfo bufferInfo{
        .buffer = uniformBuffer,
        .offset = 0,
        .range = sizeof(MeshRendererUniform)
    };

    VkWriteDescriptorSet descriptorWrite{
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .dstSet = descriptorSet,
        .dstBinding = 0,
        .dstArrayElement = 0,
        .descriptorCount = 1,
        .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .pBufferInfo = &bufferInfo
    };

    vkUpdateDescriptorSets(vk->device, 1, &descriptorWrite, 0, nullptr);
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
    // TODO Entity transformation
    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    MeshRendererUniform ubo{};

    ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.proj = glm::perspective(glm::radians(45.0f), vk->swapChainExtent.width / (float) vk->swapChainExtent.height, 0.1f, 10.0f);
    //ubo.proj[1][1] *= -1;

    void* data;
    vkMapMemory(vk->device, uniformBufferMemory, 0, sizeof(ubo), 0, &data);
        memcpy(data, &ubo, sizeof(ubo));
    vkUnmapMemory(vk->device, uniformBufferMemory);

    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, material.getAsset()->pipelineLayout, 0, 1, &descriptorSet, 0, nullptr);
    material.getAsset()->bindPipeline(commandBuffer);
    mesh.getAsset()->render(commandBuffer);
}
