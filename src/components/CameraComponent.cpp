#include "components/CameraComponent.hpp"

CameraComponent::CameraComponent(const char* _target, CameraMap* _parentMap, float _aspect)
{
    target = _target;
    parentMap = _parentMap;
    aspect = _aspect;

    projectionMatrix = glm::perspective(glm::radians(45.0f), aspect, 0.01f, 200.0f);
    projectionMatrix[1][1] *= -1;

    parentMap->emplace(target, this);
}

CameraComponent::~CameraComponent()
{
    parentMap->erase(target);
}

void CameraComponent::update(EntityTransform transform, double dt)
{
    position = transform.position;
    viewMatrix = glm::translate(glm::mat4(transform.orientation), -position);
}
