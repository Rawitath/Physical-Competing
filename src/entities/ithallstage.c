#include "../entity.h"
#include "ithallstage.h"
#include "wintext.h"
#include "timecounter.h"
#include "../timesystem.h"
#include "../scene.h"
#include "../scenecontroller.h"
#include <stdio.h>
#include "../animation.h"

#include <SDL3/SDL.h>

void ithallstage_start();
void ithallstage_poll(SDL_Event* event);
void ithallstage_loop();
void ithallstage_render(SDL_Renderer* renderer);
void ithallstage_destroy();

const char* stagePath = "res/stages/foodcenter.jpg";

void ithallstage_init(){
    ithallstage = create_entity(
            stagePath,
            &ithallstage_start,
            &ithallstage_poll,
            &ithallstage_loop,
            &ithallstage_render,
            &ithallstage_destroy
        );
    ithallstage->w *= 2.83;
    ithallstage->h *= 2.83;
}

float triggerwin_time = 0;

void ithallstage_trigger_win(const char *name)
{
    char buffer[21];
    sprintf(buffer, "%s WIN", name);
    set_text(wintext, buffer);
    triggerwin_time = 5;
}

void ithallstage_set_bg(int type)
{
    switch (type){
        case 0:
            set_image(ithallstage, stagePath);
            break;
        case 1:
            set_image(ithallstage, "res/stages/blacksquare.png");
            ithallstage->img->imgSizeX = 1440;
            ithallstage->img->imgSizeY = 1080;
            break;
    }
}

void ithallstage_start(){
    counter_set_max_time(30);
    counter_set_time(30);
}
void ithallstage_poll(SDL_Event* event){
    // if(event->type == SDL_EVENT_KEY_DOWN){
    //     if(event->key.scancode == SDL_SCANCODE_0){
    //         ithallstage_trigger_win("Asia");
    //     }
    //     if(event->key.scancode == SDL_SCANCODE_1){
    //         ithallstage_set_bg(0);
    //     }
    //     if(event->key.scancode == SDL_SCANCODE_2){
    //         ithallstage_set_bg(1);
    //     }
    // }
}

void ithallstage_loop(){
    if(triggerwin_time > 0.0){
        triggerwin_time -= get_delta();
        if(wintext->active != ACTIVE_TRUE) wintext->active = ACTIVE_TRUE;
    }
    else{
        if(wintext->active != ACTIVE_FALSE) wintext->active = ACTIVE_FALSE;
    }
}
void ithallstage_render(SDL_Renderer* renderer){
    render_entity(ithallstage, renderer, NULL);
}
void ithallstage_destroy(){
    destroy_entity(ithallstage);
}
