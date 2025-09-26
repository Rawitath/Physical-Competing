#include "../entity.h"
#include "myentity.h"

#include <SDL3/SDL.h>

void myentity_start();
void myentity_poll(SDL_Event* event);
void myentity_loop();
void myentity_render(SDL_Renderer* renderer);
void myentity_destroy();

void mysprite_init(Sprite* mysprite){
    
    mysprite->entity.x = 0.0;
    mysprite->entity.y = 0.0;
    mysprite->entity.w = 0.0;
    mysprite->entity.h = 0.0;

    mysprite->entity.start = &myentity_start;
    mysprite->entity.poll = &myentity_poll;
    mysprite->entity.loop = &myentity_loop;
    mysprite->entity.render = &myentity_render;
    mysprite->entity.destroy = &myentity_destroy;
}

void myentity_start(){
    
}
void myentity_poll(SDL_Event* event){

}
void myentity_loop(){

}
void myentity_render(SDL_Renderer* renderer){
    render_sprite(mysprite, renderer);
}
void myentity_destroy(){
    destroy_sprite(mysprite);
}
