#include "../entity.h"
#include "righthealthbar.h"
#include "../timesystem.h"
#include "../scene.h"
#include "../scenecontroller.h"
#include <stdio.h>
#include "../animation.h"

#include <SDL3/SDL.h>

void righthealthbar_start();
void righthealthbar_poll(SDL_Event* event);
void righthealthbar_loop();
void righthealthbar_render(SDL_Renderer* renderer);
void righthealthbar_destroy();

int righthealthbar_health = 100;

// SDL_FRect righthealthbar_rect;
float righthealthbar_xSize = 6 * 1.285;
float righthealthbar_xPos = 53;

void righthealthbar_init(){
    righthealthbar = ui_create_image(
             "res/stages/healthbar.png",
            &righthealthbar_start,
            &righthealthbar_poll,
            &righthealthbar_loop,
            &righthealthbar_render,
            &righthealthbar_destroy
        );
    SDL_SetSurfaceColorMod(righthealthbar->img->surface, 255, 179, 51);
}

void righthealthbar_update_bar(){
    float h = righthealthbar_health / 100.0;
    righthealthbar->w = righthealthbar_xSize * h;
    righthealthbar->x = righthealthbar_xPos + (righthealthbar_xSize * 4 * (1 - h));
}

void righthealthbar_set_health(int health)
{
    righthealthbar_health = health;
    righthealthbar_update_bar();
}

void righthealthbar_add_health(int health)
{
    righthealthbar_health += health;
    righthealthbar_update_bar();
}

void righthealthbar_subtract_health(int health)
{
    righthealthbar_health -= health;
    righthealthbar_update_bar();
}

void righthealthbar_start(){
    righthealthbar_update_bar();
    righthealthbar->x = righthealthbar_xPos;
    righthealthbar->y = 3;
    righthealthbar->w = righthealthbar_xSize;
    righthealthbar->h = 10 * 1.285;
}
void righthealthbar_poll(SDL_Event* event){
    
}

void righthealthbar_loop(){
    
}
void righthealthbar_render(SDL_Renderer* renderer){
    render_entity(righthealthbar, renderer, NULL);
}
void righthealthbar_destroy(){
    destroy_entity(righthealthbar);
}
