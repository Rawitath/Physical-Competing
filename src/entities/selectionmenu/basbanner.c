#include "../../entity.h"
#include "basbanner.h"
#include "../../timesystem.h"
#include "../../scene.h"
#include "../../scenecontroller.h"
#include <stdio.h>
#include "../../animation.h"

#include <SDL3/SDL.h>
#include "../pcutils/tweener.h"
#include "../mainmenu/menustate.h"

void basbanner_start();
void basbanner_poll(SDL_Event* event);
void basbanner_loop();
void basbanner_render(SDL_Renderer* renderer);
void basbanner_destroy();

void basbanner_init(){
    basbanner = ui_create_image(
            "res/fighters/basbanner.png",
            &basbanner_start,
            &basbanner_poll,
            &basbanner_loop,
            &basbanner_render,
            &basbanner_destroy
        );
}

void basbanner_start(){
    basbanner->x = 35;
    basbanner->y = 120;
    basbanner->w = 6 * 0.8;
    basbanner->h = 10 * 0.8;
}
SDL_Event* e;
void basbanner_poll(SDL_Event* event){
    e = event;
    // if(event->type == SDL_EVENT_KEY_DOWN){
    //     if(event->key.scancode == SDL_SCANCODE_Q){
    //         basbanner_interact();
    //     }
    // }
}

void basbanner_loop(){
    if(*menustate_state == 1){
        linear_tween_to(&basbanner->y, 65, 100 * get_delta(), 0);
    }
    else{
        linear_tween_to(&basbanner->y, 120, 100 * get_delta(), 1);
    }
}
void basbanner_render(SDL_Renderer* renderer){
    render_entity(basbanner, renderer, NULL);
}
void basbanner_destroy(){
    destroy_entity(basbanner);
}

void basbanner_interact(){
    
}
