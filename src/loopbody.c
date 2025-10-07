#include <SDL3/SDL.h>
#include <stdio.h>

#include "loopbody.h"

#include "entity.h"
#include "scene.h"

#include "scenes/myscene.h"

static SceneManager* sm;

void init(){
    sm = create_scene_manager();

     myscene_init();

     add_scene(sm, myscene);
     load_scene(sm, myscene);
}

void start(){

}

void poll(SDL_Event* event){
    SDL_PollEvent(event);

    if(sm->activeScene != NULL){
        for(int i = 0; i < sm->activeScene->entityCount; i++){
            Entity* e = get_entity_by_index(sm->activeScene, i);
            if(e && e->poll && e->active == ACTIVE_TRUE){
                e->poll(event);
            }
        }
    }
    
}
void loop(){
    if(sm->activeScene != NULL){
        for(int i = 0; i < sm->activeScene->entityCount; i++){
            Entity* e = get_entity_by_index(sm->activeScene, i);
            if(e && e->loop && e->active == ACTIVE_TRUE){
                e->loop();
            }
        }
    }
}
void render(SDL_Renderer* renderer){
    if(sm->activeScene != NULL){
        for(int i = 0; i < sm->activeScene->entityCount; i++){
            Entity* e = get_entity_by_index(sm->activeScene, i);
            if(e && e->render && e->active == ACTIVE_TRUE){
                e->render(renderer);
            }
        }
    }
}
void destroy(){
    if(sm->activeScene != NULL){
        for(int i = 0; i < sm->activeScene->entityCount; i++){
            Entity* e = get_entity_by_index(sm->activeScene, i);
            if(e && e->destroy){
                e->destroy();
            }
        }
    }

    destroy_scene_manager(sm);
}