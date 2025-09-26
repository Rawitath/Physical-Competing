#include "../entity.h"
#include "myentity.h"

#include <SDL3/SDL.h>

void start();
void poll(SDL_Event* event);
void loop();
void render(SDL_Renderer* renderer);
void destroy();

void mysprite_init(Sprite* mysprite){
    
    mysprite->entity.x = 0.0;
    mysprite->entity.y = 0.0;
    mysprite->entity.w = 0.0;
    mysprite->entity.h = 0.0;

    mysprite->entity.start = &start;
    mysprite->entity.poll = &poll;
    mysprite->entity.loop = &loop;
    mysprite->entity.render = &render;
    mysprite->entity.destroy = &destroy;
}

void start(){
    
}
void poll(SDL_Event* event){

}
void loop(){

}
void render(SDL_Renderer* renderer){
    render_sprite(mysprite, renderer);
}
void destroy(){
    destroy_sprite(mysprite);
}
