#include "../entity.h"
#include "myentity.h"
#include "../timesystem.h"
#include "../scene.h"
#include "../scenecontroller.h"
#include <stdio.h>
#include "../animation.h"

#include <SDL3/SDL.h>

#include "fighteranim.h"
#include "golfanim.h"
#include "flukeanim.h"

void myentity_start();
void myentity_poll(SDL_Event* event);
void myentity_loop();
void myentity_render(SDL_Renderer* renderer);
void myentity_destroy();

float x = 0;

void myentity_init(){
    myentity = create_entity(
            "res/lucystar.png",
            &myentity_start,
            &myentity_poll,
            &myentity_loop,
            &myentity_render,
            &myentity_destroy
        );

    golfAnim_init();
    flukeAnim_init();
    myentity->w *= 0.5;
    myentity->h *= 0.5;
}

Animation* idleLeft = NULL;

void myentity_start(){
    // printf("this will run once");
    idleLeft = create_animation("res/fighters/bas/idle_left", 15);
    set_image(myentity, idleLeft->paths[idleLeft->currentFrame]);
    

}
int fff = 0;
void myentity_poll(SDL_Event* event){
    if(event->type == SDL_EVENT_KEY_DOWN){
        if(event->key.scancode == SDL_SCANCODE_A){
            fff -= 1;
        }
        if(event->key.scancode == SDL_SCANCODE_D){
            fff += 1;
        }
    }
}

void myentity_loop(){
    fff %= 50;
    // myentity->scene->viewportZoom += 1 * get_delta();
    play_animation(myentity, golfAnim, &x, fff, 0);
    // play_animation(myentity, flukeAnim, &x, fff, 0);
}
void myentity_render(SDL_Renderer* renderer){
    render_entity(myentity, renderer, NULL);
}
void myentity_destroy(){
    destroy_fighteranim(flukeAnim);
    destroy_fighteranim(golfAnim);
    destroy_animation(idleLeft);
    destroy_entity(myentity);
}
