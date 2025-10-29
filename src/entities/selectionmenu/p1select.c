#include <SDL3/SDL.h>
#include "../../entity.h"
#include "p1select.h"
#include "../../timesystem.h"
#include "../../scene.h"
#include "../../scenecontroller.h"
#include <stdio.h>
#include "../../animation.h"

#include "allbanner.h"
#include "asiabanner.h"
#include "golfbanner.h"
#include "flukebanner.h"
#include "basbanner.h"

#include "leftfighterdisplay.h";
#include "../mainmenu/menustate.h"



void p1select_start();
void p1select_poll(SDL_Event* event);
void p1select_loop();
void p1select_render(SDL_Renderer* renderer);
void p1select_destroy();

int p1select_selectedIndex = 0;
int p1select_confirmed = 0;

void p1select_init(){
    p1select = ui_create_image(
            "res/ui/selector1.png",
            &p1select_start,
            &p1select_poll,
            &p1select_loop,
            &p1select_render,
            &p1select_destroy
        );
}

void p1select_start(){
    p1select->w = 6 * 0.8;
    p1select->h = 10 * 0.8;
}
void p1select_poll(SDL_Event* event){
    if(*menustate_state == 1){
        if(event->type == SDL_EVENT_KEY_DOWN){
            if(event->key.scancode == SDL_SCANCODE_J){
                p1select_confirmed = !p1select_confirmed;
                leftfighterdisplay_select(p1select_confirmed);
            }

            if (!p1select_confirmed) {
                if(event->key.scancode == SDL_SCANCODE_A){
                    if(p1select_selectedIndex - 1 < 0){
                        p1select_selectedIndex = allBanners_size;
                    }
                    p1select_selectedIndex--;
                } else if(event->key.scancode == SDL_SCANCODE_D){
                    if(p1select_selectedIndex + 1 > allBanners_size - 1){
                        p1select_selectedIndex = -1;
                    }
                    p1select_selectedIndex++;
                }
            }
        }
    }
    
}

void p1select_loop(){
    leftfighterdisplay_set_fighter(allFighters[p1select_selectedIndex]);
    p1select->x = allBanners[p1select_selectedIndex]->x;
    p1select->y = allBanners[p1select_selectedIndex]->y;
}
void p1select_render(SDL_Renderer* renderer){
    render_entity(p1select, renderer, NULL);
}
void p1select_destroy(){
    destroy_entity(p1select);
}
