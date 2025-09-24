#define SDL_INIT_SYSTEM_FAILED 1
#define SDL_CREATE_WINDOW_FAILED 2
#define SDL_CREATE_RENDERER_FAILED 3

#include <SDL3/SDL.h>

SDL_Window* window;
SDL_Renderer* renderer;

typedef struct SDLWindow_Config{
    const char* title;
    int w;
    int h;
    SDL_WindowFlags flags;
} SDLWindow_Config;

void main_start();
void main_loop();
void main_render();
void main_destroy();