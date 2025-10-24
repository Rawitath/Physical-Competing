#include "ss_process.h"
#include "audiostruct.h"
#include <SDL3/SDL.h>

SDL_AudioDeviceID device;
static Audio** audios;
static int audioCount = 0;

int ss_init()
{
    device = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    audios = (Audio**)malloc(sizeof(Audio*));
    return 0;
}

void* get_device(){
    return &device;
}

void ss_destroy(){
    free(audios);
    SDL_CloseAudioDevice(device);
}

int ss_play_audio(Audio *audio)
{
    // //find if entity is already with the same address exist in scene
    // for(int i = 0; i < audioCount; i++){
    //     if(audios[i] == audio){
    //         return ADD_AUDIO_ALREADY_EXIST;
    //     }
    // }
    // //resize the Audio**
    // if(audioCount > 0){
    //     Audio** temp = (Audio**)realloc(audios, (audioCount + 1) * sizeof(Audio*));
    //     if(temp == NULL){
    //         return ADD_AUDIO_ALLOCATION_FAILED;
    //     }
    //     audios = temp;
    // }

    // audios[audioCount] = audio;
    // audioCount++;
    if(!SDL_GetAudioStreamAvailable(audio->stream)){
        SDL_PutAudioStreamData(audio->stream, *audio->wav_data, *audio->wav_data_len);
    }
    else{
        SDL_ResumeAudioStreamDevice(audio->stream);
    }
    return ADD_AUDIO_SUCCESS;
}

int ss_pause_audio(Audio* audio){
    SDL_PauseAudioStreamDevice(audio->stream);
}

int ss_stop_audio(Audio *audio)
{

    // //find if entity is exist in scene
    // for(int i = 0; i < audioCount; i++){
    //     if(*(audios + i) == audio){

    //         if(i != audioCount - 1){
    //             for(int j = i; j < audioCount - 1; j++){
    //                 *(audios + j) = *(audios + j + 1);
    //             }
    //         }
    //         // 1 == 0 return 0 when scene->entityCount is not 0 otherwise, 1
    //         Audio** temp = (Audio**)realloc(audios, (audioCount - (1 == 0)) * sizeof(Audio*));
    //         if(temp == NULL){
    //             return REMOVE_AUDIO_ALLOCATION_FAILED;
    //         }
    //         audios = temp;
    //         audioCount--;

    //         return REMOVE_AUDIO_SUCCESS;
    //     }
    // }
    // return REMOVE_AUDIO_NOT_EXIST;
    
    SDL_ClearAudioStream(audio->stream);
    return ADD_AUDIO_SUCCESS;
}
