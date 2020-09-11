#pragma once

extern "C" {
#define __STDC_CONSTANT_MACROS

#include <libavutil/opt.h>
#include <libavutil/avutil.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
}

#include <AL/al.h>

#include "assets/Asset.hpp"

#include <vector>

#include "bindings/OpenALBinding.hpp"

class AudioAsset : public Asset
{
public:
    virtual void load(Binding*, const char*);
    virtual void unload();

    ALuint getBuffer() { return buffer; };
private:
    OpenALBinding* oal = nullptr;

    AVFormatContext* format = nullptr;
    AVStream* stream = nullptr;
    AVCodecContext* codec = nullptr;
    SwrContext* swr = nullptr;

    AVFrame* frame = nullptr;

    ALuint buffer;
};
