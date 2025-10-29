
#include <SDL3/SDL.h>
#include "../../entity.h"
#include "leftfighterdisplay.h"
#include "../../timesystem.h"
#include "../../scene.h"
#include "../../scenecontroller.h"
#include "../../animation.h"
#include "../fighteranim.h"


void leftfighterdisplay_start();
void leftfighterdisplay_poll(SDL_Event* event);
void leftfighterdisplay_loop();
void leftfighterdisplay_render(SDL_Renderer* renderer);
void leftfighterdisplay_destroy();

void leftfighterdisplay_init(){
    leftfighterdisplay = ui_create_image(
            NULL,
            &leftfighterdisplay_start,
            &leftfighterdisplay_poll,
            &leftfighterdisplay_loop,
            &leftfighterdisplay_render,
            &leftfighterdisplay_destroy
        );
}

FighterAnim* leftfighterdisplay_fighter = NULL;

void leftfighterdisplay_set_fighter(FighterAnim* fighter)
{
    if(leftfighterdisplay_fighter == fighter) return;
    leftfighterdisplay_fighter = fighter;
}

void leftfighterdisplay_start(){
    leftfighterdisplay->x = -20;
    leftfighterdisplay->y = 0;
    leftfighterdisplay->w = 7;
    leftfighterdisplay->h = 9;
    leftfighterdisplay->anchorX = -leftfighterdisplay->w / 2;
    leftfighterdisplay->anchorY = -leftfighterdisplay->h / 2;
}
void leftfighterdisplay_poll(SDL_Event* event){
    
}

float leftfighterdisplay_frame = 0;

void leftfighterdisplay_loop(){
    if(leftfighterdisplay_fighter != NULL){
        play_animation(leftfighterdisplay, leftfighterdisplay_fighter, &leftfighterdisplay_frame, idle, 1);
    }
}
void leftfighterdisplay_render(SDL_Renderer* renderer){
    render_entity(leftfighterdisplay, renderer, NULL);
}
void leftfighterdisplay_destroy(){
    destroy_entity(leftfighterdisplay);
}
