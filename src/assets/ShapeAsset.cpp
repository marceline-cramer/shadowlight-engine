#include "assets/ShapeAsset.hpp"

void ShapeAsset::load(Binding* _bti, const char* fileName)
{
    bti = static_cast<BulletInstance*>(_bti);

    config = bti->fs->loadConfig<ShapeConfig>(fileName);

    shape = new btBoxShape(btVector3(1, 1, 1));
}

void ShapeAsset::unload()
{
    delete shape;
    
    delete config;
}
