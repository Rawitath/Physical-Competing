#include "../../entity.h"
#include "asiabanner.h"
#include "../../timesystem.h"
#include "../../scene.h"
#include "../../scenecontroller.h"
#include <stdio.h>
#include "../../animation.h"

#include <SDL3/SDL.h>
#include "../pcutils/tweener.h"
#include "../mainmenu/menustate.h"

void asiabanner_start();
void asiabanner_poll(SDL_Event* event);
void asiabanner_loop();
void asiabanner_render(SDL_Renderer* renderer);
void asiabanner_destroy();

void asiabanner_init(){
    asiabanner = ui_create_image(
            "res/fighters/golfbanner.png",
            &asiabanner_start,
            &asiabanner_poll,
            &asiabanner_loop,
            &asiabanner_render,
            &asiabanner_destroy
        );
}

void asiabanner_start(){
    asiabanner->x = 50;
    asiabanner->y = 120;
    asiabanner->w = 6 * 0.8;
    asiabanner->h = 10 * 0.8;
}
SDL_Event* e;
void asiabanner_poll(SDL_Event* event){
    e = event;
    // if(event->type == SDL_EVENT_KEY_DOWN){
    //     if(event->key.scancode == SDL_SCANCODE_Q){
    //         asiabanner_interact();
    //     }
    // }
}

void asiabanner_loop(){
    if(*menustate_state == 1){
        linear_tween_to(&asiabanner->y, 65, 100 * get_delta(), 0.5);
    }
    else{
        linear_tween_to(&asiabanner->y, 120, 100 * get_delta(), 0.5);
    }
}
void asiabanner_render(SDL_Renderer* renderer){
    render_entity(asiabanner, renderer, NULL);
}
void asiabanner_destroy(){
    destroy_entity(asiabanner);
}

void asiabanner_interact(){
    
}
