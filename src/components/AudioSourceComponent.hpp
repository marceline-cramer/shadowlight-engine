#pragma once

#include "components/Component.hpp"

#include "assets/AssetHandle.hpp"
#include "assets/AudioAsset.hpp"

class AudioSourceComponent : public Component
{
public:
    COMPONENT_TYPE("AudioSource");
    
    AudioSourceComponent(AssetHandle<AudioAsset>&);
    virtual ~AudioSourceComponent();

    virtual void update();
    virtual void finalize(ComponentSet&, EntityTransform&);
    virtual void createBindings(lua_State*);

    ALuint getSource() { return source; };
private:
    AssetHandle<AudioAsset> audioAsset;

    EntityTransform* transform;

    ALuint source;
};
