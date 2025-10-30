#include <SDL3/SDL.h>
#include "../../entity.h"
#include "selectioncheck.h"
#include "../../timesystem.h"
#include "../../scene.h"
#include "../../scenecontroller.h"
#include <stdio.h>
#include "p1select.h"
#include "p2select.h"
#include "../roundsystem.h"
#include "shadescreen.h"

void selectioncheck_start();
void selectioncheck_poll(SDL_Event* event);
void selectioncheck_loop();
void selectioncheck_render(SDL_Renderer* renderer);
void selectioncheck_destroy();

void selectioncheck_init(){
    selectioncheck = create_entity(
            NULL,
            &selectioncheck_start,
            &selectioncheck_poll,
            &selectioncheck_loop,
            &selectioncheck_render,
            &selectioncheck_destroy
        );
}

void selectioncheck_start(){

}
void selectioncheck_poll(SDL_Event* event){

}
float selectioncheck_x = 0;
void selectioncheck_loop(){
    if(p1select_confirmed == 1 && p2select_confirmed == 1){
        if(selectioncheck_x < 0.05){
            rs_leftfighter = p1select_selectedIndex;
            rs_rightfighter = p2select_selectedIndex;
            rs_round = 0;
            rs_leftfighterpoint = 0;
            rs_rightfighterpoint = 0;
        }
        
        selectioncheck_x += get_delta();
        
        if(selectioncheck_x >= 2.2){
            shadescreen_set(1);
        }
        if(selectioncheck_x >= 4.5){
            sc_load_scene(3);
        }
    }
    
}
void selectioncheck_render(SDL_Renderer* renderer){

}
void selectioncheck_destroy(){
    destroy_entity(selectioncheck);
}