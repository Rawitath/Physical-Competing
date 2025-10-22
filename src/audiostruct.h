typedef struct SDL_AudioStream SDL_AudioStream;

typedef struct Audio {
    void **wav_data;
    int* wav_data_len;
    SDL_AudioStream *stream;
} Audio;