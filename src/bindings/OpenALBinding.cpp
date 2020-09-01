#include "bindings/OpenALBinding.hpp"

OpenALBinding::OpenALBinding()
{
    // TODO OpenAL error checking
    device = alcOpenDevice(nullptr);
    if(!device) {
        throw std::runtime_error("Failed to open OpenAL device");
    }

    context = alcCreateContext(device, nullptr);
    if(!device) {
        throw std::runtime_error("Failed to create OpenAL context");
    }

    alcMakeContextCurrent(context);
}

OpenALBinding::~OpenALBinding()
{
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

void OpenALBinding::update()
{

}
