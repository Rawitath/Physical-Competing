#include "../../entity.h"
#include "golfbanner.h"
#include "../../timesystem.h"
#include "../../scene.h"
#include "../../scenecontroller.h"
#include <stdio.h>
#include "../../animation.h"

#include <SDL3/SDL.h>
#include "../pcutils/tweener.h"
#include "../mainmenu/menustate.h"

void golfbanner_start();
void golfbanner_poll(SDL_Event* event);
void golfbanner_loop();
void golfbanner_render(SDL_Renderer* renderer);
void golfbanner_destroy();

void golfbanner_init(){
    golfbanner = ui_create_image(
            "res/ui/phonelog.png",
            &golfbanner_start,
            &golfbanner_poll,
            &golfbanner_loop,
            &golfbanner_render,
            &golfbanner_destroy
        );
}

void golfbanner_start(){
    golfbanner->x = 80;
    golfbanner->y = 120;
    golfbanner->anchorX = -5;
    golfbanner->anchorY = -5;
    golfbanner->w = 10;
    golfbanner->h = 10;
}
SDL_Event* e;
void golfbanner_poll(SDL_Event* event){
    e = event;
    // if(event->type == SDL_EVENT_KEY_DOWN){
    //     if(event->key.scancode == SDL_SCANCODE_Q){
    //         golfbanner_interact();
    //     }
    // }
}

void golfbanner_loop(){
    if(*menustate_state == 1){
        linear_tween_to(&golfbanner->y, 75, 100 * get_delta(), 0.1);
    }
    else{
        linear_tween_to(&golfbanner->y, 120, 100 * get_delta(), 0.1);
    }
}
void golfbanner_render(SDL_Renderer* renderer){
    render_entity(golfbanner, renderer, NULL);
}
void golfbanner_destroy(){
    destroy_entity(golfbanner);
}

void golfbanner_interact(){
    
}
