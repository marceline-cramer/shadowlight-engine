#pragma once

extern "C" {
#define __STDC_CONSTANT_MACROS

#include <libavutil/avutil.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
}

#include "assets/Asset.hpp"

#include "bindings/OpenALBinding.hpp"

class AudioAsset : public Asset
{
public:
    virtual ~AudioAsset();

    virtual void load(Binding*, const char*);
    void unload();
private:
    OpenALBinding* oal = nullptr;

    AVFormatContext* format = nullptr;
    AVStream* stream = nullptr;
    AVCodecContext* codec = nullptr;
    SwrContext* swr = nullptr;

    AVFrame* frame = nullptr;
};
