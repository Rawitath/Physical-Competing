#include "../entity.h"
#include "myentity.h"

#include <SDL3/SDL.h>

void myentity_start();
void myentity_poll(SDL_Event* event);
void myentity_loop();
void myentity_render(SDL_Renderer* renderer);
void myentity_destroy();

void myentity_init(){    
    myentity = create_entity(
            "res/lucystar.png",
            &myentity_start,
            &myentity_poll,
            &myentity_loop,
            &myentity_render,
            &myentity_destroy
        );
}

void myentity_start(){
    
}
void myentity_poll(SDL_Event* event){
    printf("Hi");
}
void myentity_loop(){

}
void myentity_render(SDL_Renderer* renderer){
    render_entity(myentity, renderer);
}
void myentity_destroy(){
    destroy_entity(myentity);
}
