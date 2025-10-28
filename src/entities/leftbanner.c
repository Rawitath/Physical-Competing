#include "../entity.h"
#include "leftbanner.h"
#include "../timesystem.h"
#include "../scene.h"
#include "../scenecontroller.h"
#include <stdio.h>
#include "../animation.h"

#include <SDL3/SDL.h>

void leftbanner_start();
void leftbanner_poll(SDL_Event* event);
void leftbanner_loop();
void leftbanner_render(SDL_Renderer* renderer);
void leftbanner_destroy();

const char* leftbanner_path = "res/fighters/golfbanner.png";

void leftbanner_init(){
    leftbanner = ui_create_image(
            leftbanner_path,
            &leftbanner_start,
            &leftbanner_poll,
            &leftbanner_loop,
            &leftbanner_render,
            &leftbanner_destroy
        );
}

void leftbanner_start(){
    leftbanner->x = 1;
    leftbanner->y = 1;
    leftbanner->w = 6 * 0.8;
    leftbanner->h = 10 * 0.8;
}
void leftbanner_poll(SDL_Event* event){

}

void leftbanner_loop(){

}
void leftbanner_render(SDL_Renderer* renderer){
    render_entity(leftbanner, renderer, NULL);
}
void leftbanner_destroy(){
    destroy_entity(leftbanner);
}
