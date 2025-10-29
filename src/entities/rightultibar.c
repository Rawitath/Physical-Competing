#include "../entity.h"
#include "rightultibar.h"
#include "../timesystem.h"
#include "../scene.h"
#include "../scenecontroller.h"
#include <stdio.h>
#include "../animation.h"

#include <SDL3/SDL.h>

void rightultibar_start();
void rightultibar_poll(SDL_Event* event);
void rightultibar_loop();
void rightultibar_render(SDL_Renderer* renderer);
void rightultibar_destroy();

int rightultibar_health = 100;

// SDL_FRect rightultibar_rect;
float rightultibar_xSize = 6 * 1.285;
float rightultibar_xPos = 67;

void rightultibar_init(){
    rightultibar = ui_create_image(
            "res/stages/ultibar.png",
            &rightultibar_start,
            &rightultibar_poll,
            &rightultibar_loop,
            &rightultibar_render,
            &rightultibar_destroy
        );
    SDL_SetSurfaceColorMod(rightultibar->img->surface, 51, 179, 255);
}

void rightultibar_update_bar(){
    float h = rightultibar_health / 100.0;
    rightultibar->w = rightultibar_xSize * h;
    rightultibar->x = rightultibar_xPos + (rightultibar_xSize * 2.27 * (1 - h));
}

void rightultibar_set_health(int health)
{
    rightultibar_health = health;
    rightultibar_update_bar();
}

void rightultibar_add_health(int health)
{
    rightultibar_health += health;
    rightultibar_update_bar();
}

void rightultibar_subtract_health(int health)
{
    rightultibar_health -= health;
    rightultibar_update_bar();
}

void rightultibar_start(){
    rightultibar_update_bar();
    rightultibar->x = rightultibar_xPos;
    rightultibar->y = 9;
    rightultibar->w = rightultibar_xSize;
    rightultibar->h = 10 * 1.285;
}
void rightultibar_poll(SDL_Event* event){
    if(event->key.scancode == SDL_SCANCODE_7){
            rightultibar_add_health(1);
        }
        if(event->key.scancode == SDL_SCANCODE_8){
            rightultibar_subtract_health(1);
        }
}

void rightultibar_loop(){
    
}
void rightultibar_render(SDL_Renderer* renderer){
    render_entity(rightultibar, renderer, NULL);
}
void rightultibar_destroy(){
    destroy_entity(rightultibar);
}
