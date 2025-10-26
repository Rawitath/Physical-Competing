#include "../entity.h"
#include "optionbutton.h"
#include "../timesystem.h"
#include "../scene.h"
#include "../scenecontroller.h"
#include <stdio.h>
#include "../animation.h"

#include <SDL3/SDL.h>

void optionbutton_start();
void optionbutton_poll(SDL_Event* event);
void optionbutton_loop();
void optionbutton_render(SDL_Renderer* renderer);
void optionbutton_destroy();

void optionbutton_init(){
    optionbutton = ui_create_image(
            "res/ui/phonelog.png",
            &optionbutton_start,
            &optionbutton_poll,
            &optionbutton_loop,
            &optionbutton_render,
            &optionbutton_destroy
        );
}

void optionbutton_start(){
    optionbutton->x = 50;
    optionbutton->y = 75;
    optionbutton->anchorX = -5;
    optionbutton->anchorY = -5;
    optionbutton->w = 10;
    optionbutton->h = 10;
}
void optionbutton_poll(SDL_Event* event){
    // if(event->type == SDL_EVENT_KEY_DOWN){
    //     if(event->key.scancode == SDL_SCANCODE_Q){
    //         optionbutton_interact();
    //     }
    // }
}

void optionbutton_loop(){


}
void optionbutton_render(SDL_Renderer* renderer){
    render_entity(optionbutton, renderer, NULL);

}
void optionbutton_destroy(){

    destroy_entity(optionbutton);
}

void optionbutton_interact(){
    printf("Option");
}
