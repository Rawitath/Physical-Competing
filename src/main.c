#include <stdio.h>

#include "main.h"
#include "loopbody.h"

int main(){

    SDLWindow_Config config;

    config.title = "Physical Competing";
    config.w = 1280;
    config.h = 720;
    config.flags = SDL_WINDOW_HIGH_PIXEL_DENSITY;
    
    if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)){
        printf("%s", SDL_GetError());
        return SDL_INIT_SYSTEM_FAILED;
    }
    
    window = SDL_CreateWindow(config.title, config.w, config.h, config.flags);
    if(window == NULL){
        printf("%s", SDL_GetError());
        return SDL_CREATE_WINDOW_FAILED;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if(renderer == NULL){
        printf("%s", SDL_GetError());
        return SDL_CREATE_RENDERER_FAILED;
    }
    
    SDL_Event event;

    start();

    do{
        poll(&event);

        loop();

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        render();

        SDL_RenderPresent(renderer);
    }
    while(event.type != SDL_EVENT_QUIT);

    destroy();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}