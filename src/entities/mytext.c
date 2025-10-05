#include "mytext.h"
#include "../entity.h"
#include "../timesystem.h"
#include "../scene.h"

#include <SDL3/SDL.h>

void mytext_start();
void mytext_poll(SDL_Event* event);
void mytext_loop();
void mytext_render(SDL_Renderer* renderer);
void mytext_destroy();

void mytext_init(){    
    mytext = ui_create_text(
            "res/UPCDL.TTF",
            24,
            &mytext_start,
            &mytext_poll,
            &mytext_loop,
            &mytext_render,
            &mytext_destroy
        );
    mytext->x = 50;
    mytext->y = 100;
    set_text(mytext, "EEEEE");
}

void mytext_start(){
    
}
void mytext_poll(SDL_Event* event){
    
}
void mytext_loop(){
    set_font_size(mytext, get_font_size(mytext) + 5 * get_delta());
}
void mytext_render(SDL_Renderer* renderer){
    render_entity(mytext, renderer);
}
void mytext_destroy(){
    destroy_entity(mytext);
}
