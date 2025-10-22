typedef struct SDL_Surface SDL_Surface;

typedef struct AnimOffset{
    unsigned int index;
    int x;
    int y;
} AnimOffset;

typedef struct Animation{
    const char** paths;
    unsigned int imageCount;
    unsigned int currentFrame;
    float fps;
    AnimOffset* offsets;
} Animation;

Animation* create_animation(const char* animDir, float fps);
int destroy_animation(Animation* anim);