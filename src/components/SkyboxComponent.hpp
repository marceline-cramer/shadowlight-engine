#pragma once

#include "assets/AssetHandle.hpp"
#include "assets/EnvironmentMapAsset.hpp"

#include "components/Component.hpp"

class SkyboxComponent;
using SkyboxComponentSet = std::set<SkyboxComponent*>;

class SkyboxComponent : public Component
{
public:
    COMPONENT_TYPE("Skybox");

    SkyboxComponent(SkyboxComponentSet*, AssetHandle<EnvironmentMapAsset>&);
    ~SkyboxComponent();
private:
    SkyboxComponentSet* parentSet;

    AssetHandle<EnvironmentMapAsset> environmentMap;
};
