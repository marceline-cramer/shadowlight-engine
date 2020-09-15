#pragma once

#include "assets/AssetHandle.hpp"
#include "assets/MeshAsset.hpp"
#include "assets/MaterialAsset.hpp"

#include "components/Component.hpp"

class MeshRendererComponent : public Component
{
public:
    COMPONENT_TYPE("MeshRenderer");

    MeshRendererComponent(AssetHandle<MeshAsset>&, AssetHandle<MaterialAsset>&);
    ~MeshRendererComponent();
private:
};
