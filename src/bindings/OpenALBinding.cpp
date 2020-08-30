#include "bindings/OpenALBinding.hpp"

OpenALBinding::OpenALBinding()
{
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

}

void OpenALBinding::update()
{
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
}
