#pragma once

#include "components/Component.hpp"

#include "assets/AssetHandle.hpp"
#include "assets/AudioAsset.hpp"

class AudioSourceComponent : public Component
{
public:
    AudioSourceComponent(AssetHandle<AudioAsset>&);
    virtual ~AudioSourceComponent();

    virtual void update();
    virtual const char* getComponentType() { return ComponentType; };

    virtual void finalize(ComponentSet&);

    virtual void createBindings(lua_State*);

    ALuint getSource() { return source; };

    static constexpr const char* ComponentType = "AudioSource";
private:
    AssetHandle<AudioAsset> audioAsset;

    ALuint source;
};
