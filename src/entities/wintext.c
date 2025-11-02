#include "wintext.h"
#include "../entity.h"
#include "../timesystem.h"
#include "../scene.h"

#include <SDL3/SDL.h>

void wintext_start();
void wintext_poll(SDL_Event* event);
void wintext_loop();
void wintext_render(SDL_Renderer* renderer);
void wintext_destroy();

void wintext_init(){    
    wintext = ui_create_text(
            "res/Bangers-Regular.ttf",
            150,
            &wintext_start,
            &wintext_poll,
            &wintext_loop,
            &wintext_render,
            &wintext_destroy
        );
}

void wintext_start(){
    wintext->x = 50;
    wintext->y = 50;
    set_text_color(wintext, 253, 47, 6, SDL_ALPHA_OPAQUE);
}
void wintext_poll(SDL_Event* event){
    
}
void wintext_loop(){
    
}
void wintext_render(SDL_Renderer* renderer){
    render_entity(wintext, renderer, NULL);
}
void wintext_destroy(){
    destroy_entity(wintext);
}
