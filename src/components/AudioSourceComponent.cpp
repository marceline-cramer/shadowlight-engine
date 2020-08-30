#include "components/AudioSourceComponent.hpp"

static int AudioSourceComponent_play(lua_State* L)
{
    AudioSourceComponent* source = static_cast<AudioSourceComponent*>(lua_touserdata(L, lua_upvalueindex(1)));
    alSourcePlay(source->getSource());

    return 0;
}

AudioSourceComponent::AudioSourceComponent(AssetHandle<AudioAsset>& _audioAsset)
{
    audioAsset = _audioAsset;

    // TODO Add position/velocity tied to RigidBody
    // TODO 
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, audioAsset.getAsset()->getBuffer());
}

AudioSourceComponent::~AudioSourceComponent()
{
    alDeleteSources(1, &source);
}

void AudioSourceComponent::update()
{

}

void AudioSourceComponent::finalize(ComponentSet&)
{

}

void AudioSourceComponent::createBindings(lua_State* L)
{

}
