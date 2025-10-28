#include "../entity.h"
#include "lefthealthbar.h"
#include "../timesystem.h"
#include "../scene.h"
#include "../scenecontroller.h"
#include <stdio.h>
#include "../animation.h"

#include <SDL3/SDL.h>

void lefthealthbar_start();
void lefthealthbar_poll(SDL_Event* event);
void lefthealthbar_loop();
void lefthealthbar_render(SDL_Renderer* renderer);
void lefthealthbar_destroy();

int lefthealthbar_health = 100;

// SDL_FRect lefthealthbar_rect;
float lefthealthbar_xSize = 6 * 1.285;
float lefthealthbar_xPos = 12;

void lefthealthbar_init(){
    lefthealthbar = ui_create_image(
            "res/stages/healthbar.png",
            &lefthealthbar_start,
            &lefthealthbar_poll,
            &lefthealthbar_loop,
            &lefthealthbar_render,
            &lefthealthbar_destroy
        );
    SDL_SetSurfaceColorMod(lefthealthbar->img->surface, 255, 179, 51);
}

void lefthealthbar_update_bar(){
    float h = lefthealthbar_health / 100.0;
    lefthealthbar->w = lefthealthbar_xSize * h;
    lefthealthbar->x = lefthealthbar_xPos - (lefthealthbar_xSize / 2 * h);
}

void lefthealthbar_set_health(int health)
{
    lefthealthbar_health = health;
    lefthealthbar_update_bar();
}

void lefthealthbar_add_health(int health)
{
    lefthealthbar_health += health;
    lefthealthbar_update_bar();
}

void lefthealthbar_subtract_health(int health)
{
    lefthealthbar_health -= health;
    lefthealthbar_update_bar();
}

void lefthealthbar_start(){
    lefthealthbar_update_bar();
    lefthealthbar->x = lefthealthbar_xPos;
    lefthealthbar->y = 3;
    lefthealthbar->w = lefthealthbar_xSize;
    lefthealthbar->h = 10 * 1.285;
}
void lefthealthbar_poll(SDL_Event* event){
    if(event->type == SDL_EVENT_KEY_DOWN){
        if(event->key.scancode == SDL_SCANCODE_1){
            lefthealthbar_subtract_health(1);
        }
        if(event->key.scancode == SDL_SCANCODE_2){
            lefthealthbar_add_health(1);
        }
    }
}

void lefthealthbar_loop(){
    
}
void lefthealthbar_render(SDL_Renderer* renderer){
    render_entity(lefthealthbar, renderer, NULL);
}
void lefthealthbar_destroy(){
    destroy_entity(lefthealthbar);
}
