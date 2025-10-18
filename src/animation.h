typedef struct SDL_Surface SDL_Surface;

typedef struct CharQueueNode CharQueueNode;

typedef struct CharQueueNode{
    CharQueueNode* next;
    char* data;
} CharQueueNode;

typedef struct CharQueue{
    unsigned int queueSize;
    CharQueueNode* front;
} CharQueue;

typedef struct AnimOffset{
    unsigned int index;
    int x;
    int y;
} AnimOffset;

typedef struct Animation{
    const char* name;
    SDL_Surface* surface;
    unsigned int fps;
    AnimOffset* offsets;
} Animation;

int init_animation(const char* ansqPath);
int destroy_animation(const char* name);