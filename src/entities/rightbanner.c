#include "../entity.h"
#include "rightbanner.h"
#include "../timesystem.h"
#include "../scene.h"
#include "../scenecontroller.h"
#include <stdio.h>
#include "../animation.h"

#include <SDL3/SDL.h>

void rightbanner_start();
void rightbanner_poll(SDL_Event* event);
void rightbanner_loop();
void rightbanner_render(SDL_Renderer* renderer);
void rightbanner_destroy();

const char* rightbanner_path = "res/fighters/flukebanner.png";

void rightbanner_init(){
    rightbanner = ui_create_image(
            rightbanner_path,
            &rightbanner_start,
            &rightbanner_poll,
            &rightbanner_loop,
            &rightbanner_render,
            &rightbanner_destroy
        );
}

void rightbanner_start(){
    rightbanner->x = 85;
    rightbanner->y = 1;
    rightbanner->w = 6 * 0.8;
    rightbanner->h = 10 * 0.8;
}
void rightbanner_poll(SDL_Event* event){

}

void rightbanner_loop(){

}
void rightbanner_render(SDL_Renderer* renderer){
    render_entity(rightbanner, renderer, NULL);
}
void rightbanner_destroy(){
    destroy_entity(rightbanner);
}
