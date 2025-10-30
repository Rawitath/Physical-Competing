#include <SDL3/SDL.h>
#include "../../entity.h"
#include "shadescreen.h"
#include "../../timesystem.h"
#include "../../scene.h"
#include "../mainmenu/menustate.h"
#include "../pcutils/tweener.h"

void shadescreen_start();
void shadescreen_poll(SDL_Event* event);
void shadescreen_loop();
void shadescreen_render(SDL_Renderer* renderer);
void shadescreen_destroy();

void shadescreen_init(){
    shadescreen = ui_create_image(
            "res/stages/blacksquare.png",
            &shadescreen_start,
            &shadescreen_poll,
            &shadescreen_loop,
            &shadescreen_render,
            &shadescreen_destroy
        );
}

int shadescreen_alpha = 0;
int shadescreen_state = 0;

void shadescreen_start(){
    shadescreen->w = 100;
    shadescreen->h = 100;
}
void shadescreen_poll(SDL_Event* event){

}
void shadescreen_set(int state){
    shadescreen_state = state;
}

void shadescreen_loop(){
    if (shadescreen_state== 1) {
        linear_tween_to_int(&shadescreen_alpha, 255, 255 * get_delta(), 1);
    } else {
        linear_tween_to_int(&shadescreen_alpha, 0, 255 * get_delta(), 0);
    }
}
void shadescreen_render(SDL_Renderer* renderer){
    SDL_SetSurfaceAlphaMod(shadescreen->img->surface, shadescreen_alpha);
    render_entity(shadescreen, renderer, NULL);
}
void shadescreen_destroy(){
    destroy_entity(shadescreen);
}