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

void lefthealthbar_init(){
    lefthealthbar = ui_create_text(
            "res/UPCDL.TTF",
            48,
            &lefthealthbar_start,
            &lefthealthbar_poll,
            &lefthealthbar_loop,
            &lefthealthbar_render,
            &lefthealthbar_destroy
        );
    set_text_color(lefthealthbar, 255, 255, 255, SDL_ALPHA_OPAQUE);
}

void lefthealthbar_update_text(){
    char buf[100];
    sprintf(buf, "%d%%", lefthealthbar_health);
    set_text(lefthealthbar, buf);
}

void lefthealthbar_set_health(int health)
{
    lefthealthbar_health = health;
    lefthealthbar_update_text();
}

void lefthealthbar_add_health(int health)
{
    lefthealthbar_health += health;
    lefthealthbar_update_text();
}

void lefthealthbar_subtract_health(int health)
{
    lefthealthbar_health -= health;
    lefthealthbar_update_text();
}

void lefthealthbar_start(){
    lefthealthbar_update_text();
    lefthealthbar->x = 10;
    lefthealthbar->y = 10;
}
void lefthealthbar_poll(SDL_Event* event){
    
}

void lefthealthbar_loop(){
    
}
void lefthealthbar_render(SDL_Renderer* renderer){
    render_entity(lefthealthbar, renderer, NULL);
}
void lefthealthbar_destroy(){
    destroy_entity(lefthealthbar);
}
