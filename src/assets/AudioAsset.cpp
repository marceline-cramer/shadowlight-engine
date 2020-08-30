#include "assets/AudioAsset.hpp"

AudioAsset::~AudioAsset()
{
    unload();
}

void AudioAsset::load(Binding* _oal, const char* fileName)
{
    unload();

    // TODO A lot of these FFMPEG calls are deprecated, please update

    oal = static_cast<OpenALBinding*>(_oal);

    format = avformat_alloc_context();
    if(avformat_open_input(&format, fileName, nullptr, nullptr)) {
        throw std::runtime_error("Could not open AudioAsset " + std::string(fileName));
    }

    if (avformat_find_stream_info(format, NULL) < 0) {
        throw std::runtime_error("Could not retrieve stream info from AudioAsset " + std::string(fileName));
    }

    int stream_index = -1;
    for(int i = 0; i < format->nb_streams; i++) {
        if(format->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO) {
            stream_index = i;
            break;
        }
    }

    if(stream_index == -1) {
        throw std::runtime_error("Could not retrieve audio stream from AudioAsset " + std::string(fileName));
    }

    stream = format->streams[stream_index];

    codec = stream->codec;
    if(avcodec_open2(codec, avcodec_find_decoder(codec->codec_id), nullptr) < 0) {
        throw std::runtime_error("Failed to open decoder for AudioAsset " + std::string(fileName));
    }

    swr = swr_alloc();
    av_opt_set_int(swr, "in_channel_count",  codec->channels, 0);
    av_opt_set_int(swr, "out_channel_count", 1, 0);
    av_opt_set_int(swr, "in_channel_layout",  codec->channel_layout, 0);
    av_opt_set_int(swr, "out_channel_layout", AV_CH_LAYOUT_MONO, 0);
    av_opt_set_int(swr, "in_sample_rate", codec->sample_rate, 0);
    av_opt_set_int(swr, "out_sample_rate", oal->getSampleRate(), 0);
    av_opt_set_sample_fmt(swr, "in_sample_fmt",  codec->sample_fmt, 0);
    av_opt_set_sample_fmt(swr, "out_sample_fmt", AV_SAMPLE_FMT_DBL,  0);
    swr_init(swr);
    if (!swr_is_initialized(swr)) {
        throw std::runtime_error("Resampler has not been properly initialized");
    }

    // TODO Load each audio frame into a vector
    std::vector<char> bufferData;

    // TODO Come up with better AL error checking
    // Load sound data into buffer
    alGenBuffers(1, &buffer);
    if(alGetError() != AL_NO_ERROR) {
        throw std::runtime_error("Failed to create OpenAL buffer for AudioAsset " + std::string(fileName));
    }

    ALenum bufferFormat = AL_FORMAT_MONO16;

    alBufferData(buffer, bufferFormat, bufferData.data(), bufferData.size(), oal->getSampleRate());
}

void AudioAsset::unload()
{
    alDeleteBuffers(1, &buffer);
    
    //av_frame_free(&frame);
    swr_free(&swr);
    avcodec_close(codec);
    avformat_free_context(format);
}
