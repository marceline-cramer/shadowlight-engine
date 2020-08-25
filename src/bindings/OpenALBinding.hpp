#pragma once

#include <stdexcept>

#include <AL/al.h>
#include <AL/alc.h>

class OpenALBinding
{
public:
    OpenALBinding();
    ~OpenALBinding();

    void update();
private:
    ALCdevice* device;
    ALCcontext* context;
};
