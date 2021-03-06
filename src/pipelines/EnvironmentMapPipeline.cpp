#include "pipelines/EnvironmentMapPipeline.hpp"

EnvironmentMapPipeline::EnvironmentMapPipeline(VulkanBinding* _vk)
{
    vk = _vk;
    gBuffer = vk->getGBuffer();

    environmentMapPool = new AssetPool<EnvironmentMapAsset>(vk);

    skyboxShader = new SkyboxShader(vk->getInstance());

    createSkyboxSphere();
    createSkyboxPipeline();
}

EnvironmentMapPipeline::~EnvironmentMapPipeline()
{
    vkDestroyPipeline(vk->device, skyboxGraphicsPipeline, nullptr);

    vkDestroyBuffer(vk->device, indexBuffer, nullptr);
    vkFreeMemory(vk->device, indexBufferMemory, nullptr);
    vkDestroyBuffer(vk->device, vertexBuffer, nullptr);
    vkFreeMemory(vk->device, vertexBufferMemory, nullptr);

    delete environmentMapPool;

    delete skyboxShader;
}

void EnvironmentMapPipeline::render(VkCommandBuffer commandBuffer, CameraComponent* camera)
{
    if(!skyboxSet.empty()) {
        VkDeviceSize offsets[] = {0};
        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, skyboxGraphicsPipeline);
        vkCmdBindVertexBuffers(commandBuffer, 0, 1, &vertexBuffer, offsets);
        vkCmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT32);

        for(auto skybox : skyboxSet) {
            skybox->render(commandBuffer, camera);
            vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(sphereGeometry.indices.size()), 1, 0, 0, 0);
        }
    }
}

SkyboxComponent* EnvironmentMapPipeline::createSkybox(const char* environmentMapName)
{
    AssetHandle<EnvironmentMapAsset> environmentMap;
    environmentMapPool->load(environmentMapName, environmentMap);

    return new SkyboxComponent(&skyboxSet, skyboxShader, environmentMap);
}

void EnvironmentMapPipeline::createSkyboxSphere()
{
    Geometry::createUVSphere(10, 10, 1.0, &sphereGeometry);

    VkDeviceSize vertexBufferSize = sizeof(Geometry::GeometryVertex) * sphereGeometry.vertices.size();
    VkDeviceSize indexBufferSize = sizeof(Geometry::GeometryIndex) * sphereGeometry.indices.size();

    vk->getInstance()->createBuffer(vertexBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);
    vk->getInstance()->createBuffer(indexBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

    vk->getInstance()->stageBuffer(vertexBuffer, vertexBufferSize, sphereGeometry.vertices.data());
    vk->getInstance()->stageBuffer(indexBuffer, indexBufferSize, sphereGeometry.indices.data());
}

void EnvironmentMapPipeline::createSkyboxPipeline()
{
    auto shaderStages = skyboxShader->getStages();

    auto vertexBindingDescription = Geometry::GeometryVertex::getBindingDescription();
    auto vertexAttributeDescriptions = Geometry::GeometryVertex::getAttributeDescriptions();

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .vertexBindingDescriptionCount = 1,
        .pVertexBindingDescriptions = &vertexBindingDescription,
        .vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexAttributeDescriptions.size()),
        .pVertexAttributeDescriptions = vertexAttributeDescriptions.data()
    };

    VkPipelineInputAssemblyStateCreateInfo inputAssembly{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        .primitiveRestartEnable = VK_FALSE
    };

    VkPipelineRasterizationStateCreateInfo rasterizer{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .depthClampEnable = VK_FALSE,
        .rasterizerDiscardEnable = VK_FALSE,
        .polygonMode = VK_POLYGON_MODE_FILL,
        .cullMode = VK_CULL_MODE_BACK_BIT,
        .frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE,
        .depthBiasEnable = VK_FALSE,
        .depthBiasConstantFactor = 0.0f,
        .depthBiasClamp = 0.0f,
        .depthBiasSlopeFactor = 0.0f,
        .lineWidth = 1.0f
    };

    auto viewportState = gBuffer->getViewportState();
    auto multisampling = gBuffer->getMultisampleState();
    auto colorBlending = gBuffer->getColorBlendState();

    // Use only the non-PBR-stenciled fragments for skybox
    VkPipelineDepthStencilStateCreateInfo depthStencil{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
        .depthTestEnable = VK_FALSE,
        .depthWriteEnable = VK_FALSE,
        .depthCompareOp = VK_COMPARE_OP_LESS,
        .depthBoundsTestEnable = VK_FALSE,
        .stencilTestEnable = VK_TRUE,
        .front = {
            .failOp = VK_STENCIL_OP_KEEP,
            .passOp = VK_STENCIL_OP_KEEP,
            .depthFailOp = VK_STENCIL_OP_KEEP,
            .compareOp = VK_COMPARE_OP_EQUAL,
            .compareMask = 0xFFFFFFFF,
            .writeMask = 0xFFFFFFFF,
            .reference = 0
        },
        .back = {},
        .minDepthBounds = 0.0,
        .maxDepthBounds = 1.0
    };

    VkGraphicsPipelineCreateInfo pipelineInfo{
        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .stageCount = static_cast<uint32_t>(shaderStages.size()),
        .pStages = shaderStages.data(),
        .pVertexInputState = &vertexInputInfo,
        .pInputAssemblyState = &inputAssembly,
        .pViewportState = &viewportState,
        .pRasterizationState = &rasterizer,
        .pMultisampleState = &multisampling,
        .pDepthStencilState = &depthStencil,
        .pColorBlendState = &colorBlending,
        .pDynamicState = nullptr,
        .layout = skyboxShader->getPipelineLayout(),
        .renderPass = vk->mainRenderPass,
        .subpass = 1,
        .basePipelineHandle = VK_NULL_HANDLE,
        .basePipelineIndex = -1
    };

    if(vkCreateGraphicsPipelines(vk->device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &skyboxGraphicsPipeline) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create skybox graphics pipeline");
    }
}
