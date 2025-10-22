typedef Uint8 Uint8;
typedef Uint32 Uint32;

typedef struct Audio {
    Uint8 **wav_data;
    Uint32* wav_data_len;
    SDL_AudioStream *stream;
} Audio;