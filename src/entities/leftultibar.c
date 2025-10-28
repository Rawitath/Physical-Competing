#include "../entity.h"
#include "leftultibar.h"
#include "../timesystem.h"
#include "../scene.h"
#include "../scenecontroller.h"
#include <stdio.h>
#include "../animation.h"

#include <SDL3/SDL.h>

void leftultibar_start();
void leftultibar_poll(SDL_Event* event);
void leftultibar_loop();
void leftultibar_render(SDL_Renderer* renderer);
void leftultibar_destroy();

int leftultibar_health = 100;

// SDL_FRect leftultibar_rect;
float leftultibar_xSize = 6 * 1.285;
float leftultibar_xPos = 14;

void leftultibar_init(){
    leftultibar = ui_create_image(
            "res/stages/ultibar.png",
            &leftultibar_start,
            &leftultibar_poll,
            &leftultibar_loop,
            &leftultibar_render,
            &leftultibar_destroy
        );
    SDL_SetSurfaceColorMod(leftultibar->img->surface, 51, 179, 255);
}

void leftultibar_update_bar(){
    float h = leftultibar_health / 100.0;
    leftultibar->w = leftultibar_xSize * h;
    leftultibar->x = leftultibar_xPos - (leftultibar_xSize / 2 * h);
}

void leftultibar_set_health(int health)
{
    leftultibar_health = health;
    leftultibar_update_bar();
}

void leftultibar_add_health(int health)
{
    leftultibar_health += health;
    leftultibar_update_bar();
}

void leftultibar_subtract_health(int health)
{
    leftultibar_health -= health;
    leftultibar_update_bar();
}

void leftultibar_start(){
    leftultibar_update_bar();
    leftultibar->x = leftultibar_xPos;
    leftultibar->y = 9;
    leftultibar->w = leftultibar_xSize;
    leftultibar->h = 10 * 1.285;
}
void leftultibar_poll(SDL_Event* event){
    if(event->key.scancode == SDL_SCANCODE_3){
            leftultibar_subtract_health(1);
        }
        if(event->key.scancode == SDL_SCANCODE_4){
            leftultibar_add_health(1);
        }
}

void leftultibar_loop(){
    
}
void leftultibar_render(SDL_Renderer* renderer){
    render_entity(leftultibar, renderer, NULL);
}
void leftultibar_destroy(){
    destroy_entity(leftultibar);
}
