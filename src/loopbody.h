typedef union SDL_Event SDL_Event;

void init();
void poll(SDL_Event* event);
void loop();
void render();
void destroy();