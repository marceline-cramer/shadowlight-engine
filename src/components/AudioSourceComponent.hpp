#pragma once

#include "components/Component.hpp"

#include "assets/AssetHandle.hpp"
#include "assets/AudioAsset.hpp"

class AudioSourceComponent : public Component
{
public:
    COMPONENT_TYPE("AudioSource");
    
    AudioSourceComponent(AssetHandle<AudioAsset>&);
    ~AudioSourceComponent();

    virtual void update(EntityTransform, double);    
    virtual void finalize(ComponentSet&) {};
    virtual void createBindings(lua_State*);

    ALuint getSource() { return source; };
private:
    AssetHandle<AudioAsset> audioAsset;

    EntityTransform* transform;

    ALuint source;
};
