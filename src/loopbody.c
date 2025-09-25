#include <SDL3/SDL.h>
#include <stdio.h>

#include "loopbody.h"

#include "entity.h"
#include "scene.h"

void start(){
    Entity entity;
    entity.id = 0;
    entity.x = 1;
    entity.y = 5;
    entity.w = 10;
    entity.h = 10;

    Entity entity1;
    entity1.id = 1;
    entity1.x = 3;
    entity1.y = 6;
    entity1.w = 14;
    entity1.h = 12;

    Entity entity2;
    entity2.id = 1;
    entity2.x = 3;
    entity2.y = 6;
    entity2.w = 18;
    entity2.h = 12;

    Scene scene;
    init_scene(&scene, 0);
    printf("%u ", scene.entityCount);
    add_entity(&scene, &entity);
    printf("%u ", scene.entityCount);
    add_entity(&scene, &entity1);
    printf("%u \n", scene.entityCount);

    printf("%f\n", (*(scene.entities))->w);
    printf("%f\n", (*(scene.entities + 1))->w);

    remove_entity(&scene, &entity1);
    printf("%u \n", scene.entityCount);
}
void poll(SDL_Event* event){
    SDL_PollEvent(event);
}
void loop(){
    
}
void render(){

}
void destroy(){

}