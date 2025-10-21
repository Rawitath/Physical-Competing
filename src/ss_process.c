#include "ss_process.h"
#include <SDL3/SDL.h>

SDL_AudioDeviceID device;

int ss_init()
{
    device = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    return 0;
}

void* get_device(){
    return &device;
}

void ss_destroy(){
    SDL_CloseAudioDevice(device);
}