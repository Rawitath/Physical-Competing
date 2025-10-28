#include "../../entity.h"
#include "startbutton.h"
#include "startbuttontext.h"
#include "../../timesystem.h"
#include "../../scene.h"
#include "../../scenecontroller.h"
#include <stdio.h>
#include "../../animation.h"
#include "menustate.h"
#include "../pcutils/tweener.h"

#include <SDL3/SDL.h>

void startbutton_start();
void startbutton_poll(SDL_Event* event);
void startbutton_loop();
void startbutton_render(SDL_Renderer* renderer);
void startbutton_destroy();

void startbutton_init(){
    startbutton = ui_create_image(
            "res/ui/tornpaper.png",
            &startbutton_start,
            &startbutton_poll,
            &startbutton_loop,
            &startbutton_render,
            &startbutton_destroy
        );
    // startbuttontext_init();
}

void startbutton_start(){
    startbutton->x = 25;
    startbutton->y = 75;
    startbutton->img->imgSizeX = 100;
    startbutton->img->imgSizeY = 100;
    startbutton->anchorX = -12.5;
    startbutton->anchorY = -12.5;
    startbutton->w = 25;
    startbutton->h = 25;

    // if(startbuttontext != NULL) startbuttontext->start();
    // add_entity(startbutton->scene, startbuttontext);
    // set_text(startbuttontext, "Hi");
}
void startbutton_poll(SDL_Event* event){
    // if(event->type == SDL_EVENT_KEY_DOWN){
    //     if(event->key.scancode == SDL_SCANCODE_Q){
    //         startbutton_interact();
    //     }
    // }
    // if(startbuttontext != NULL) startbuttontext->poll(event);
}

void startbutton_loop(){
    if(*menustate_state == 0){
        linear_tween_to(&startbutton->y, 75, 100 * get_delta(), 0.5);
    }
    else{
        linear_tween_to(&startbutton->y, 120, 100 * get_delta(), 0.5);
    }
    // if(startbuttontext != NULL) startbuttontext->loop();
    // startbuttontext->x = startbutton->x;
    // startbuttontext->y = startbutton->y;

}
void startbutton_render(SDL_Renderer* renderer){
    render_entity(startbutton, renderer, NULL);
    // if(startbuttontext != NULL) startbuttontext->render(renderer);
}
void startbutton_destroy(){
    // startbuttontext->destroy();
    destroy_entity(startbutton);
}

void startbutton_interact(){
    *menustate_state = 1;
}
