#include "components/CameraComponent.hpp"

CameraComponent::CameraComponent(const char* _target, float _aspect)
{
    target = _target;
    aspect = _aspect;
}

CameraComponent::~CameraComponent()
{

}

void CameraComponent::update()
{
    viewMatrix = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    projectionMatrix = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 200.0f);
    projectionMatrix[1][1] *= -1;
}
