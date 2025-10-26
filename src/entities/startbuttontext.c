#include "startbuttontext.h"
#include "../entity.h"
#include "../timesystem.h"
#include "../scene.h"

#include <SDL3/SDL.h>

void startbuttontext_start();
void startbuttontext_poll(SDL_Event* event);
void startbuttontext_loop();
void startbuttontext_render(SDL_Renderer* renderer);
void startbuttontext_destroy();

void startbuttontext_init(){    
    startbuttontext = ui_create_text(
            "res/UPCDL.TTF",
            48,
            &startbuttontext_start,
            &startbuttontext_poll,
            &startbuttontext_loop,
            &startbuttontext_render,
            &startbuttontext_destroy
        );
}

void startbuttontext_start(){
    
}
void startbuttontext_poll(SDL_Event* event){
    
}
void startbuttontext_loop(){
    
}
void startbuttontext_render(SDL_Renderer* renderer){
    render_entity(startbuttontext, renderer, NULL);
}
void startbuttontext_destroy(){
    destroy_entity(startbuttontext);
    startbuttontext = NULL;
}
