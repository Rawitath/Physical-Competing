#include "../entity.h"
#include "timecounter.h"
#include "../timesystem.h"
#include "../scene.h"
#include "../scenecontroller.h"
#include <stdio.h>
#include "../animation.h"

#include <SDL3/SDL.h>

void timecounter_start();
void timecounter_poll(SDL_Event* event);
void timecounter_loop();
void timecounter_render(SDL_Renderer* renderer);
void timecounter_destroy();

int maxTime = 10;
int currentTime;

void counter_set_max_time(int time)
{
    maxTime = time;
}

void counter_set_time(int time)
{
    currentTime = time;
    char buffer[7];
    sprintf(buffer, "%d", currentTime);
    set_text(timecounter, buffer);
}

void timecounter_init(){
    timecounter = ui_create_text(
            "res/UPCDL.TTF",
            72,
            &timecounter_start,
            &timecounter_poll,
            &timecounter_loop,
            &timecounter_render,
            &timecounter_destroy
        );
    currentTime = maxTime;
    counter_set_time(currentTime);
}

void timecounter_start(){
    timecounter->x = 50;
    timecounter->y = 10;
}
void timecounter_poll(SDL_Event* event){

}

float timecounter_x = 0;

void decrease_time(float* x){
    if(*x < 1){
        *x += get_delta();
    }
    else{
        currentTime--;

        char buffer[7];
        sprintf(buffer, "%d", currentTime);
        set_text(timecounter, buffer);

        *x = 0;
    }
}

void timecounter_loop(){
    if(currentTime > 0){
        decrease_time(&timecounter_x);
    }
}
void timecounter_render(SDL_Renderer* renderer){
    render_entity(timecounter, renderer, NULL);
}
void timecounter_destroy(){
    destroy_entity(timecounter);
}
