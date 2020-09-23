#pragma once

#include "components/Component.hpp"

class CameraComponent;
using CameraMap = std::map<std::string, CameraComponent*>;

class CameraComponent : public Component
{
public:
    COMPONENT_TYPE("Camera");

    CameraComponent(const char*, float);
    ~CameraComponent();

    virtual void update();

    glm::mat4 getViewMatrix() { return viewMatrix; }
    glm::mat4 getProjectionMatrix() { return projectionMatrix; }
private:
    std::string target;
    float aspect;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
};
