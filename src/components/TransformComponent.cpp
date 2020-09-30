#include "components/TransformComponent.hpp"

TransformComponent::TransformComponent(TransformConfig& config)
{
    transform.position = config.position;
    // TODO TransformConfig orientation
    transform.orientation = glm::quat();
}
