typedef union SDL_Event SDL_Event;

void start();
void poll(SDL_Event* event);
void loop();
void render();
void destroy();