#include "../../entity.h"
#include "flukebanner.h"
#include "../../timesystem.h"
#include "../../scene.h"
#include "../../scenecontroller.h"
#include <stdio.h>
#include "../../animation.h"

#include <SDL3/SDL.h>
#include "../pcutils/tweener.h"
#include "../mainmenu/menustate.h"

void flukebanner_start();
void flukebanner_poll(SDL_Event* event);
void flukebanner_loop();
void flukebanner_render(SDL_Renderer* renderer);
void flukebanner_destroy();

void flukebanner_init(){
    flukebanner = ui_create_image(
            "res/fighters/flukebanner.png",
            &flukebanner_start,
            &flukebanner_poll,
            &flukebanner_loop,
            &flukebanner_render,
            &flukebanner_destroy
        );
}

void flukebanner_start(){
    flukebanner->x = 20;
    flukebanner->y = 120;
    flukebanner->w = 6 * 0.8;
    flukebanner->h = 10 * 0.8;
}
SDL_Event* e;
void flukebanner_poll(SDL_Event* event){
    e = event;
    // if(event->type == SDL_EVENT_KEY_DOWN){
    //     if(event->key.scancode == SDL_SCANCODE_Q){
    //         flukebanner_interact();
    //     }
    // }
}

void flukebanner_loop(){
    if(*menustate_state == 1){
        linear_tween_to(&flukebanner->y, 65, 100 * get_delta(), 0);
    }
    else{
        linear_tween_to(&flukebanner->y, 120, 100 * get_delta(), 1);
    }
}
void flukebanner_render(SDL_Renderer* renderer){
    render_entity(flukebanner, renderer, NULL);
}
void flukebanner_destroy(){
    destroy_entity(flukebanner);
}

void flukebanner_interact(){
    
}
