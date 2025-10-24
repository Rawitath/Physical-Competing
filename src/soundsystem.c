#include <SDL3/SDL.h>
#include "soundsystem.h"
#include "ss_process.h"
#include <stdlib.h>

Audio* create_audio(const char* path){
    Audio* audio = (Audio*)malloc(sizeof(Audio));
    audio->wav_data = (void**)malloc(sizeof(void*));
    audio->wav_data_len = (int*)malloc(sizeof(int));

    SDL_AudioSpec spec;
    if(!SDL_LoadWAV(path, &spec, audio->wav_data, audio->wav_data_len)){
        return CREATE_AUDIO_LOAD_FAILED;
    }
    audio->stream = SDL_CreateAudioStream(&spec, NULL);

    if (!audio->stream) {
        return CREATE_AUDIO_STREAM_FAILED;
    } else if (!SDL_BindAudioStream(*(SDL_AudioDeviceID*)get_device(), audio->stream)) { 
        return CREATE_AUDIO_BIND_FAILED;
    }
    return audio;
}

int set_loop(Audio *audio, int loop)
{
    return 0;
}

int play_audio(Audio *audio)
{
    return ss_play_audio(audio);
}

int pause_audio(Audio *audio)
{
    return ss_pause_audio(audio);
}

int stop_audio(Audio *audio)
{
    return ss_stop_audio(audio);
}

void destroy_audio(Audio* audio){
    free(*audio->wav_data);
    free(audio->wav_data);
    free(audio->wav_data_len);
    SDL_DestroyAudioStream(audio->stream);
    free(audio);
}