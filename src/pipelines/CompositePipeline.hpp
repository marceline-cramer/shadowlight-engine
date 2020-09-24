#pragma once

#include "pipelines/Pipeline.hpp"

class CompositePipeline : public Pipeline
{
public:
    CompositePipeline(VulkanBinding*);
    
    virtual void render(VkCommandBuffer, CameraComponent*);
private:
};
