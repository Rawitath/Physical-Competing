#include <SDL3/SDL.h>
#include "../../entity.h"
#include "rightfighterdisplay.h"
#include "../../timesystem.h"
#include "../../scene.h"
#include "../../scenecontroller.h"
#include "../../animation.h"
#include "../fighteranim.h"
#include "../mainmenu/menustate.h"

void rightfighterdisplay_start();
void rightfighterdisplay_poll(SDL_Event* event);
void rightfighterdisplay_loop();
void rightfighterdisplay_render(SDL_Renderer* renderer);
void rightfighterdisplay_destroy();

void rightfighterdisplay_init(){
    rightfighterdisplay = create_entity(
            NULL,
            &rightfighterdisplay_start,
            &rightfighterdisplay_poll,
            &rightfighterdisplay_loop,
            &rightfighterdisplay_render,
            &rightfighterdisplay_destroy
        );
}

FighterAnim* rightfighterdisplay_fighter = NULL;

void rightfighterdisplay_set_fighter(FighterAnim* fighter)
{
    if(rightfighterdisplay_fighter == fighter) return;
    rightfighterdisplay_fighter = fighter;
}

int rightfighterdisplay_selected = 0;

void rightfighterdisplay_select(int select)
{
    rightfighterdisplay_selected = select;
}

void rightfighterdisplay_start(){
    rightfighterdisplay->x = 500;
    rightfighterdisplay->y = -200;
    rightfighterdisplay->w = 80;
    rightfighterdisplay->h = 80;
    rightfighterdisplay->anchorX = -rightfighterdisplay->w / 2;
    rightfighterdisplay->anchorY = -rightfighterdisplay->h / 2;
    set_text_color(rightfighterdisplay, 253, 47, 6, SDL_ALPHA_OPAQUE);
}
void rightfighterdisplay_poll(SDL_Event* event){
    
}

float rightfighterdisplay_frame = 0;

void rightfighterdisplay_loop(){
    if(rightfighterdisplay_fighter != NULL){
        if(rightfighterdisplay_selected == 0){
            play_animation(rightfighterdisplay, rightfighterdisplay_fighter, &rightfighterdisplay_frame, idle, 0);
        }
        else{
            play_animation(rightfighterdisplay, rightfighterdisplay_fighter, &rightfighterdisplay_frame, win, 0);
        }
    }
}
void rightfighterdisplay_render(SDL_Renderer* renderer){
    if(*menustate_state == 1)
    render_entity(rightfighterdisplay, renderer, NULL);
}
void rightfighterdisplay_destroy(){
    destroy_entity(rightfighterdisplay);
}
