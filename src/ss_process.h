typedef struct Audio Audio;
#define ADD_AUDIO_ALREADY_EXIST 1
#define ADD_AUDIO_ALLOCATION_FAILED 2
#define ADD_AUDIO_SUCCESS 0

#define REMOVE_AUDIO_NOT_EXIST 1
#define REMOVE_AUDIO_ALLOCATION_FAILED 2
#define REMOVE_AUDIO_SUCCESS 0

int ss_init();
void* get_device();
void ss_destroy();

int ss_play_audio(Audio* audio);
int ss_pause_audio(Audio* audio);
int ss_stop_audio(Audio* audio);