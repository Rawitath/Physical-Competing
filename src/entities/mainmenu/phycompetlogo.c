#include "../../entity.h"
#include "phycompetlogo.h"
#include "../../timesystem.h"
#include "../pcutils/tweener.h"
#include "menustate.h"

#include <SDL3/SDL.h>

// Forward declarations
void phycompetlogo_start();
void phycompetlogo_poll(SDL_Event* event);
void phycompetlogo_loop();
void phycompetlogo_render(SDL_Renderer* renderer);
void phycompetlogo_destroy();

// Global entity pointer
Entity* phycompetlogo;

void phycompetlogo_init(){
    phycompetlogo = ui_create_image(
            "res/ui/phycompet.png",
            &phycompetlogo_start,
            &phycompetlogo_poll,
            &phycompetlogo_loop,
            &phycompetlogo_render,
            &phycompetlogo_destroy
        );
}

void phycompetlogo_start(){
    phycompetlogo->x = 18;
    phycompetlogo->y = 10;
    phycompetlogo->w = 4;
    phycompetlogo->h = 4;
    phycompetlogo->anchorX = -phycompetlogo->w / 2;
    phycompetlogo->anchorY = -phycompetlogo->h / 2;
}

void phycompetlogo_poll(SDL_Event* event){
    // No event handling needed for the logo
}

void phycompetlogo_loop(){
    if(*menustate_state == 0){
        linear_tween_to(&phycompetlogo->y, 10, 100 * get_delta(), 1);
    }
    else{
        linear_tween_to(&phycompetlogo->y, -40, 100 * get_delta(), 0);
    }
}

void phycompetlogo_render(SDL_Renderer* renderer){
    render_entity(phycompetlogo, renderer, NULL);
}

void phycompetlogo_destroy(){
    destroy_entity(phycompetlogo);
}