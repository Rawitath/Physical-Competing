typedef union SDL_Event SDL_Event;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Surface SDL_Surface;
typedef struct Scene Scene;

typedef struct Entity{
    int id;
    const char* name;
    float x;
    float y;
    float w;
    float h;

    void (*start)();
    void (*poll)(SDL_Event* event);
    void (*loop)();
    void (*render)(SDL_Renderer* renderer);
    void (*destroy)();
    //Image Render
    SDL_Surface* surface;

    Scene* scene;
} Entity;

Entity* create_entity(
    const char* imgPath,
    void (*start)(), 
    void (*poll)(SDL_Event* event), 
    void (*loop)(),
    void (*render)(SDL_Renderer* renderer),
    void (*destroy)()
    );

void destroy_entity(Entity* entity);

#define RENDER_SUCCESS 0
#define RENDER_SURFACE_NULL 1

int render_entity(Entity* entity, SDL_Renderer* renderer);
