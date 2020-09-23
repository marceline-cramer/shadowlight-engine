#pragma once

#include "components/Component.hpp"

class CameraComponent;
using CameraMap = std::map<std::string, CameraComponent*>;

class CameraComponent : public Component
{
public:
    COMPONENT_TYPE("Camera");

    CameraComponent(const char*, CameraMap*, float);
    ~CameraComponent();

    virtual void update();
    virtual void finalize(ComponentSet&, EntityTransform&);

    glm::mat4 getViewMatrix() { return viewMatrix; }
    glm::mat4 getProjectionMatrix() { return projectionMatrix; }
private:
    std::string target;
    CameraMap* parentMap;
    float aspect;

    EntityTransform* transform;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
};
