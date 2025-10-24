typedef struct SDL_AudioStream SDL_AudioStream;

#define SET_PAUSED_FALSE 0
#define SET_PAUSED_TRUE 1

#define SET_LOOP_INFINITY -1
#define SET_LOOP_ONCE 0

typedef struct Audio {
    void **wav_data;
    int* wav_data_len;
    int loop;
    int paused;
    SDL_AudioStream *stream;
} Audio;