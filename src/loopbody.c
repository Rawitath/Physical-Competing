#include <SDL3/SDL.h>
#include <stdio.h>

#include "loopbody.h"

#include "entity.h"
#include "scene.h"

#include "scenes/menuscene.h"
#include "scenes/myscene.h"
#include "scenes/anotherscene.h"
#include "scenes/ithallscene.h"
#include "sc_process.h"
#include "ss_process.h"

static SceneManager* sm;

void init(){
    sm = create_scene_manager();
    sc_init(sm);
    ss_init();

    menuscene_init();
    myscene_init();
    anotherscene_init();
    ithallscene_init();

    add_scene(sm, menuscene);
    add_scene(sm, myscene);
    add_scene(sm, anotherscene);
    add_scene(sm, ithallscene);
    load_scene(sm, 3);
}

void start(){
    if(sm->activeScene != NULL){
        for(int i = 0; i < sm->activeScene->entityCount; i++){
            Entity* e = get_entity_by_index(sm->activeScene, i);
            if(e && e->needStart  && e->active == ACTIVE_TRUE && e->start){
                e->start();
                e->needStart = 0;
            }
        }
    }
}

void poll(SDL_Event* event){
    SDL_PollEvent(event);

    if(sm->activeScene != NULL){
        for(int i = 0; i < sm->activeScene->entityCount; i++){
            Entity* e = get_entity_by_index(sm->activeScene, i);
            if(e && e->poll && e->active == ACTIVE_TRUE && e->needStart == 0){
                e->poll(event);
            }
        }
    }
    
}
void loop(){
    if(sm->activeScene != NULL){
        for(int i = 0; i < sm->activeScene->entityCount; i++){
            Entity* e = get_entity_by_index(sm->activeScene, i);
            if(e && e->loop && e->active == ACTIVE_TRUE && e->needStart == 0){
                e->loop();
            }
        }
    }
    ss_loop();
}
void render(SDL_Renderer* renderer){
    if(sm->activeScene != NULL){
        for(int i = 0; i < sm->activeScene->entityCount; i++){
            Entity* e = get_entity_by_index(sm->activeScene, i);
            if(e && e->render && e->active == ACTIVE_TRUE && e->needStart == 0){
                e->render(renderer);
            }
        }
    }
}
void destroy(){
    // if(sm->activeScene != NULL){
    //     for(int i = 0; i < sm->activeScene->entityCount; i++){
    //         Entity* e = get_entity_by_index(sm->activeScene, i);
    //         if(e && e->destroy){
    //             e->destroy();
    //         }
    //     }
    // }
    sm->activeScene->unload();

    destroy_scene_manager(sm);
    ss_destroy();
}