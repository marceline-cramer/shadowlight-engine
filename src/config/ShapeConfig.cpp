#include "config/ShapeConfig.hpp"

ShapeConfig::ShapeConfig(ConfigData& configData)
{
    std::string typeString = getConfigString(configData, "type");

    if(typeString == "plane") {
        shapeType = SHAPE_TYPE_PLANE;

        glm::vec3 normal = getConfigVec3(configData, "normal");
        shapeVector = btVector3(normal.x, normal.y, normal.z);
    } else if(typeString == "sphere") {
        shapeType = SHAPE_TYPE_SPHERE;

        shapeScalar = getConfigDouble(configData, "radius");
    } else {
        throw std::runtime_error("Unrecognized shape type");
    }
}
