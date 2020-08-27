#include "components/AudioSourceComponent.hpp"

AudioSourceComponent::AudioSourceComponent(AssetHandle<AudioAsset>& _audioAsset)
{
    audioAsset = _audioAsset;
}

AudioSourceComponent::~AudioSourceComponent()
{

}

void AudioSourceComponent::update()
{

}

void AudioSourceComponent::finalize(ComponentSet&)
{

}
