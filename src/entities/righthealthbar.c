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

void righthealthbar_init(){
    righthealthbar = ui_create_text(
            "res/UPCDL.TTF",
            48,
            &righthealthbar_start,
            &righthealthbar_poll,
            &righthealthbar_loop,
            &righthealthbar_render,
            &righthealthbar_destroy
        );
    set_text_color(righthealthbar, 255, 255, 255, SDL_ALPHA_OPAQUE);
}

void righthealthbar_update_text(){
    char buf[100];
    sprintf(buf, "%d%%", righthealthbar_health);
    set_text(righthealthbar, buf);
}

void righthealthbar_set_health(int health)
{
    righthealthbar_health = health;
    righthealthbar_update_text();
}

void righthealthbar_add_health(int health)
{
    righthealthbar_health += health;
    righthealthbar_update_text();
}

void righthealthbar_subtract_health(int health)
{
    righthealthbar_health -= health;
    righthealthbar_update_text();
}

void righthealthbar_start(){
    righthealthbar_update_text();
    righthealthbar->x = 90;
    righthealthbar->y = 10;
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
