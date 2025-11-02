#include "../../entity.h"
#include "menubg.h"
#include "../../timesystem.h"
#include "../../scene.h"
#include "../../scenecontroller.h"
#include "menustate.h"

#include <SDL3/SDL.h>

void menubg_start();
void menubg_poll(SDL_Event* event);
void menubg_loop();
void menubg_render(SDL_Renderer* renderer);
void menubg_destroy();

void menubg_init(){
    menubg = ui_create_image(
            "res/ui/itbuilding.jpg",
            &menubg_start,
            &menubg_poll,
            &menubg_loop,
            &menubg_render,
            &menubg_destroy
        );
}

void menubg_start(){
    menubg->x = -25;
    menubg->y = 0;
    menubg->w = 10;
    menubg->h = 12;
}
void menubg_poll(SDL_Event* event){
    if(event->type == SDL_EVENT_KEY_DOWN){
        if(event->key.scancode == SDL_SCANCODE_ESCAPE){
            *menustate_state = 0;
        }
    }
}

void menubg_loop(){
    
}
void menubg_render(SDL_Renderer* renderer){
    render_entity(menubg, renderer, NULL);
}
void menubg_destroy(){
    destroy_entity(menubg);
}
