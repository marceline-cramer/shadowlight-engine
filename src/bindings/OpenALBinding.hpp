#pragma once

#include <stdexcept>

#include <AL/al.h>
#include <AL/alc.h>

#include "bindings/Binding.hpp"

class OpenALBinding : public Binding
{
public:
    OpenALBinding();
    ~OpenALBinding();

    void update();
private:
    ALCdevice* device;
    ALCcontext* context;
};
