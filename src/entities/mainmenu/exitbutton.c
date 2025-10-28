#include "../../entity.h"
#include "exitbutton.h"
#include "../../timesystem.h"
#include "../../scene.h"
#include "../../scenecontroller.h"
#include <stdio.h>
#include "../../animation.h"
#include "../pcutils/tweener.h"
#include "menustate.h"

#include <SDL3/SDL.h>

void exitbutton_start();
void exitbutton_poll(SDL_Event* event);
void exitbutton_loop();
void exitbutton_render(SDL_Renderer* renderer);
void exitbutton_destroy();

void exitbutton_init(){
    exitbutton = ui_create_image(
            "res/ui/tornpaper.png",
            &exitbutton_start,
            &exitbutton_poll,
            &exitbutton_loop,
            &exitbutton_render,
            &exitbutton_destroy
        );
}

void exitbutton_start(){
    exitbutton->x = 75;
    exitbutton->y = 75;
    exitbutton->img->imgSizeX = 100;
    exitbutton->img->imgSizeY = 100;
    exitbutton->anchorX = -12.5;
    exitbutton->anchorY = -12.5;
    exitbutton->w = 25;
    exitbutton->h = 25;
}
SDL_Event* e;
void exitbutton_poll(SDL_Event* event){
    e = event;
    // if(event->type == SDL_EVENT_KEY_DOWN){
    //     if(event->key.scancode == SDL_SCANCODE_Q){
    //         exitbutton_interact();
    //     }
    // }
}

void exitbutton_loop(){
    if(*menustate_state == 0){
        linear_tween_to(&exitbutton->y, 75, 100 * get_delta(), 0.5);
    }
    else{
        linear_tween_to(&exitbutton->y, 120, 100 * get_delta(), 0.5);
    }
}
void exitbutton_render(SDL_Renderer* renderer){
    render_entity(exitbutton, renderer, NULL);
}
void exitbutton_destroy(){
    destroy_entity(exitbutton);
}

void exitbutton_interact(){
    e->type = SDL_EVENT_QUIT;
}
