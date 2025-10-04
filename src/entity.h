typedef union SDL_Event SDL_Event;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Surface SDL_Surface;
typedef struct TTF_Font TTF_Font;
typedef struct Scene Scene;

#define ENTITY_TYPE_SPRITE 0
#define ENTITY_TYPE_TEXT 1
#define ENTITY_TYPE_UIIMAGE 2
#define ENTITY_TYPE_UITEXT 3

#define ENTITY_INVALID_TYPE -1

#define SET_SUCCESS 0

typedef struct ImageContainer{
    SDL_Surface* surface;
    float pixelRatio;
    int imgSizeX;
    int imgSizeY;
} ImageContainer;

typedef struct TextContainer{
    TTF_Font* font;
    int r;
    int g;
    int b;
    int a;
    const char* text;
    float size;
    int horizontalAlign;
    int verticalAlign;
} TextContainer;

typedef struct Entity{
    int type;
    int id;
    const char* name;
    float x;
    float y;
    float w;
    float h;
    float anchorX;
    float anchorY;

    void (*start)();
    void (*poll)(SDL_Event* event);
    void (*loop)();
    void (*render)(SDL_Renderer* renderer);
    void (*destroy)();
    
    //Specific Container
    ImageContainer* img;
    TextContainer* txt;

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

Entity* ui_create_text(
    const char* fontPath,
    float size,
    void (*start)(), 
    void (*poll)(SDL_Event* event), 
    void (*loop)(),
    void (*render)(SDL_Renderer* renderer),
    void (*destroy)()
    );

void destroy_entity(Entity* entity);

#define RENDER_SUCCESS 0
#define RENDER_SURFACE_NULL 1
#define RENDER_FONT_NULL 1
#define RENDER_UNKNOWN_TYPE 2

int set_image(Entity* entity, const char* imgPath);
int set_text(Entity* entity, const char* text);
int set_font(Entity* entity, const char* fontPath);
int render_entity(Entity* entity, SDL_Renderer* renderer);
