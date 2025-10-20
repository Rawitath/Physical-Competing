#include "../entity.h"
#include "myentity.h"
#include "../timesystem.h"
#include "../scene.h"
#include "../scenecontroller.h"
#include <stdio.h>
#include "../animation.h"

#include <SDL3/SDL.h>

void myentity_start();
void myentity_poll(SDL_Event* event);
void myentity_loop();
void myentity_render(SDL_Renderer* renderer);
void myentity_destroy();

void myentity_init(){
    myentity = create_entity(
            "res/lucystar.png",
            &myentity_start,
            &myentity_poll,
            &myentity_loop,
            &myentity_render,
            &myentity_destroy
        );
}

Animation* idleLeft = NULL;

void myentity_start(){
    // printf("this will run once");
    idleLeft = create_animation("res/fighters/bas/idle_left", 15);
}
void myentity_poll(SDL_Event* event){
    if(event->type == SDL_EVENT_KEY_DOWN){
        if(event->key.scancode == SDL_SCANCODE_D){
            sc_load_scene(1);
        }
    }
}
void myentity_loop(){
    myentity->scene->viewportZoom += 1 * get_delta();
}
void myentity_render(SDL_Renderer* renderer){
    render_entity(myentity, renderer, NULL);
}
void myentity_destroy(){
    destroy_animation(idleLeft);
    destroy_entity(myentity);
}
