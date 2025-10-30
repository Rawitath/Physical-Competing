#include <SDL3/SDL.h>
#include "../../entity.h"
#include "p2select.h"
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
#include "rightfighterdisplay.h";
#include "../mainmenu/menustate.h"


void p2select_start();
void p2select_poll(SDL_Event* event);
void p2select_loop();
void p2select_render(SDL_Renderer* renderer);
void p2select_destroy();

int p2select_selectedIndex = 0;
int p2select_confirmed = 0;

void p2select_init(){
    p2select = ui_create_image(
            "res/ui/selector2.png",
            &p2select_start,
            &p2select_poll,
            &p2select_loop,
            &p2select_render,
            &p2select_destroy
        );
}

void p2select_start(){
    p2select->w = 6 * 0.8;
    p2select->h = 10 * 0.8;
}
void p2select_poll(SDL_Event* event){
    if(*menustate_state == 1){
        if(event->type == SDL_EVENT_KEY_DOWN){
            if(event->key.scancode == SDL_SCANCODE_KP_1){
                p2select_confirmed = !p2select_confirmed;
                rightfighterdisplay_select(p2select_confirmed);
            }

            if (!p2select_confirmed) {
                if(event->key.scancode == SDL_SCANCODE_LEFT){
                    if(p2select_selectedIndex - 1 < 0){
                        p2select_selectedIndex = allBanners_size;
                    }
                    p2select_selectedIndex--;
                }
                else if(event->key.scancode == SDL_SCANCODE_RIGHT){
                    if(p2select_selectedIndex + 1 > allBanners_size - 1){
                        p2select_selectedIndex = -1;
                    }
                    p2select_selectedIndex++;
                }
            }
        }
    }
}

void p2select_loop(){
    rightfighterdisplay_set_fighter(allFighters[p2select_selectedIndex]);
    p2select->x = allBanners[p2select_selectedIndex]->x;
    p2select->y = allBanners[p2select_selectedIndex]->y;
}
void p2select_render(SDL_Renderer* renderer){
    render_entity(p2select, renderer, NULL);
}
void p2select_destroy(){
    destroy_entity(p2select);
}
