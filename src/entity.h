typedef union SDL_Event SDL_Event;
typedef struct SDL_Renderer SDL_Renderer;

typedef struct Entity{
    int id;
    float x;
    float y;
    float w;
    float h;

    void (*start)();
    void (*poll)(SDL_Event* event);
    void (*loop)();
    void (*render)(SDL_Renderer* renderer);
    void (*destroy)();
} Entity;

typedef struct Sprite{
    Entity entity;
    const char* imgPath;
} Sprite;
