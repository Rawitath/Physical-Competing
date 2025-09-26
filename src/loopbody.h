typedef union SDL_Event SDL_Event;
typedef struct SDL_Renderer SDL_Renderer;

void init();
void poll(SDL_Event* event);
void loop();
void render(SDL_Renderer* renderer);
void destroy();