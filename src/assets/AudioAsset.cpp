#include "assets/AudioAsset.hpp"

AudioAsset::~AudioAsset()
{
    unload();
}

void AudioAsset::load(Binding* _oal, const char* fileName)
{
    unload();

    oal = static_cast<OpenALBinding*>(_oal);

    format = avformat_alloc_context();
    if(avformat_open_input(&format, fileName, nullptr, nullptr)) {
        throw std::runtime_error("Could not open AudioAsset " + std::string(fileName));
    }

    if (avformat_find_stream_info(format, NULL) < 0) {
        throw std::runtime_error("Could not retrieve stream info from AudioAsset " + std::string(fileName));
    }
}

void AudioAsset::unload()
{
    //av_frame_free(&frame);
    //swr_free(&swr);
    //avcodec_close(codec);
    avformat_free_context(format);
}
