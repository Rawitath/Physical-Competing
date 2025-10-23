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

void ithallstage_init(){
    ithallstage = create_entity(
            "res/stages/ithall.jpg",
            &ithallstage_start,
            &ithallstage_poll,
            &ithallstage_loop,
            &ithallstage_render,
            &ithallstage_destroy
        );
}

float triggerwin_time = 0;

void ithallstage_trigger_win(const char *name)
{
    char buffer[21];
    sprintf(buffer, "%s WIN", name);
    set_text(wintext, buffer);
    triggerwin_time = 5;
}

void ithallstage_start(){
    counter_set_max_time(30);
    counter_set_time(30);
}
void ithallstage_poll(SDL_Event* event){
    if(event->type == SDL_EVENT_KEY_DOWN){
        if(event->key.scancode == SDL_SCANCODE_0){
            ithallstage_trigger_win("Asia");
        }
    }
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
