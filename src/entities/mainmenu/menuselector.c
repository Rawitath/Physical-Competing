#include "../../entity.h"
#include "menuselector.h"
#include "../../timesystem.h"
#include "../../scene.h"
#include "../../scenecontroller.h"
#include <stdio.h>
#include "../../animation.h"

#include "startbutton.h"
#include "optionbutton.h"
#include "exitbutton.h"

#include <SDL3/SDL.h>

void menuselector_start();
void menuselector_poll(SDL_Event* event);
void menuselector_loop();
void menuselector_render(SDL_Renderer* renderer);
void menuselector_destroy();

Entity* buttons[3];
int selectedIndex = 0;

void menuselector_init(){
    menuselector = ui_create_image(
            "res/ui/jaramedflag.png",
            &menuselector_start,
            &menuselector_poll,
            &menuselector_loop,
            &menuselector_render,
            &menuselector_destroy
        );
}

void menuselector_start(){
    // printf("this will run once");
    menuselector->anchorX = -5;
    menuselector->anchorY = -5;
    menuselector->img->imgSizeX = 100;
    menuselector->img->imgSizeX = 100;
    menuselector->w = 10;
    exitbutton->h = 10;
    buttons[0] = startbutton;
    buttons[1] = optionbutton;
    buttons[2] = exitbutton;
}
void menuselector_poll(SDL_Event* event){
    if(event->type == SDL_EVENT_KEY_DOWN){
        if(event->key.scancode == SDL_SCANCODE_W){
            if(selectedIndex - 1 < 0){
                selectedIndex = 3;
            }
            selectedIndex--;
        }
        else if(event->key.scancode == SDL_SCANCODE_S){
            if(selectedIndex + 1 > 2){
                selectedIndex = -1;
            }
            selectedIndex++;
        }
        else if(event->key.scancode == SDL_SCANCODE_Q){
            switch(selectedIndex){
                case 0:
                    startbutton_interact();
                    break;
                case 1:
                    optionbutton_interact();
                    break;
                case 2:
                    exitbutton_interact();
                    break;
            }
        }
    }
}

void menuselector_loop(){
    menuselector->x = buttons[selectedIndex]->x + menuselector->w / 2;
    menuselector->y = buttons[selectedIndex]->y + menuselector->h;
}
void menuselector_render(SDL_Renderer* renderer){
    render_entity(menuselector, renderer, NULL);
}
void menuselector_destroy(){
    destroy_entity(menuselector);
}
