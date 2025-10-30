#include "../entity.h"
#include "stageui.h"
#include "../timesystem.h"
#include "../scene.h"
#include "../scenecontroller.h"
#include <stdio.h>
#include "../animation.h"

#include <SDL3/SDL.h>

void stageui_start();
void stageui_poll(SDL_Event* event);
void stageui_loop();
void stageui_render(SDL_Renderer* renderer);
void stageui_destroy();

void stageui_init(){
    stageui = ui_create_image(
            "res/stages/stageUI.png",
            &stageui_start,
            &stageui_poll,
            &stageui_loop,
            &stageui_render,
            &stageui_destroy
        );
}

void stageui_start(){
    stageui->w = 6 * 1.285;
    stageui->h = 10 * 1.285;
}
void stageui_poll(SDL_Event* event){

}

void stageui_loop(){

}
void stageui_render(SDL_Renderer* renderer){
    render_entity(stageui, renderer, NULL);
}
void stageui_destroy(){
    destroy_entity(stageui);
}
