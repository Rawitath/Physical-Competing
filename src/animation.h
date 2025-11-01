typedef struct SDL_Surface SDL_Surface;

typedef struct AnimOffset{
    unsigned int index;
    float x;
    float y;
    float w;
    float h;
} AnimOffset;

typedef struct Animation{
    const char** paths;
    unsigned int imageCount;
    unsigned int currentFrame;
    unsigned int frameSkip;
    float fps;
    AnimOffset* offsets;
} Animation;

Animation* create_animation(const char* animDir, float fps);
int destroy_animation(Animation* anim);