typedef union SDL_Event SDL_Event;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Surface SDL_Surface;

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

Entity* create_entity(
    void (*start)(), 
    void (*poll)(SDL_Event* event), 
    void (*loop)(),
    void (*render)(SDL_Renderer* renderer),
    void (*destroy)()
    );

void destroy_entity(Entity* entity);

#define RENDER_SUCCESS 0
#define RENDER_SURFACE_NULL 1

typedef struct Sprite{
    Entity entity;
    SDL_Surface* surface;
} Sprite;

Sprite* create_sprite(const char* imgPath, Entity entity);

int render_sprite(Sprite* sprite, SDL_Renderer* renderer);
void destroy_sprite(Sprite* sprite);
