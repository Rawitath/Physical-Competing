
#include <SDL3/SDL.h>
#include "../../entity.h"
#include "leftfighterdisplay.h"
#include "../../timesystem.h"
#include "../../scene.h"
#include "../../scenecontroller.h"
#include "../../animation.h"
#include "../fighteranim.h"
#include "../mainmenu/menustate.h"


void leftfighterdisplay_start();
void leftfighterdisplay_poll(SDL_Event* event);
void leftfighterdisplay_loop();
void leftfighterdisplay_render(SDL_Renderer* renderer);
void leftfighterdisplay_destroy();

void leftfighterdisplay_init(){
    leftfighterdisplay = create_entity(
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

int leftfighterdisplay_selected = 0;


void leftfighterdisplay_select(int select)
{
    leftfighterdisplay_selected = select;
}

void leftfighterdisplay_start(){
    leftfighterdisplay->x = -460;
    leftfighterdisplay->y = -200;
    leftfighterdisplay->w = 80;
    leftfighterdisplay->h = 80;
    leftfighterdisplay->anchorX = -leftfighterdisplay->w / 2;
    leftfighterdisplay->anchorY = -leftfighterdisplay->h / 2;
}
void leftfighterdisplay_poll(SDL_Event* event){
    
}

float leftfighterdisplay_frame = 0;

void leftfighterdisplay_loop(){
    if(leftfighterdisplay_fighter != NULL){
        if(leftfighterdisplay_selected == 0){
            play_animation(leftfighterdisplay, leftfighterdisplay_fighter, &leftfighterdisplay_frame, idle, 1);
        }
        else{
            play_animation(leftfighterdisplay, leftfighterdisplay_fighter, &leftfighterdisplay_frame, win, 1);
        }
        
    }
}
void leftfighterdisplay_render(SDL_Renderer* renderer){
    if(*menustate_state == 1)
    render_entity(leftfighterdisplay, renderer, NULL);
}
void leftfighterdisplay_destroy(){
    destroy_entity(leftfighterdisplay);
}
