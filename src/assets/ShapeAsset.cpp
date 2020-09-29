#include "assets/ShapeAsset.hpp"

void ShapeAsset::load(Binding* _bti, const char* fileName)
{
    bti = static_cast<BulletInstance*>(_bti);

    config = bti->fs->loadConfig<ShapeConfig>(fileName);

    switch(config->shapeType) {
    case SHAPE_TYPE_PLANE:
        shape = new btStaticPlaneShape(config->shapeVector, 0.0);
        break;
    case SHAPE_TYPE_SPHERE:
        shape = new btSphereShape(config->shapeScalar);
        break;
    default:
        throw std::runtime_error("Unrecognized shape asset type");
    }
}

void ShapeAsset::unload()
{
    delete shape;
    
    delete config;
}
