#include "components/SkyboxComponent.hpp"

SkyboxComponent::SkyboxComponent(SkyboxComponentSet* _parentSet, AssetHandle<EnvironmentMapAsset>& _environmentMap)
{
    parentSet = _parentSet;
    environmentMap = _environmentMap;

    parentSet->insert(this);
}

SkyboxComponent::~SkyboxComponent()
{
    parentSet->erase(this);
}
