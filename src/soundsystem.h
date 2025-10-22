#include "audiostruct.h"

#define CREATE_AUDIO_LOAD_FAILED NULL
#define CREATE_AUDIO_STREAM_FAILED NULL
#define CREATE_AUDIO_BIND_FAILED NULL
#define CREATE_AUDIO_SUCCESS 0

#define SET_LOOP_LOOP 1
#define SET_LOOP_ONCE 0

Audio* create_audio(const char* path);
int set_loop(Audio* audio, int loop);
int play_audio(Audio* audio);
int pause_audio(Audio* audio);
int stop_audio(Audio* audio);

void destroy_audio(Audio* audio);