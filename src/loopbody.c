#include <SDL3/SDL.h>
#include <stdio.h>

#include "loopbody.h"

#include "entity.h"
#include "scene.h"

#include "scenes/myscene.h"

static SceneManager* sm;

void init(){
    sm = create_scene_manager();

    add_scene(sm, &myscene);
}
void poll(SDL_Event* event){
    SDL_PollEvent(event);

    for(int i = 0; i < sm->activeScene->entityCount; i++){
        Entity e = *(*(sm->activeScene->entities + i));
        e.poll(event);
    }
}
void loop(){
    for(int i = 0; i < sm->activeScene->entityCount; i++){
        Entity e = *(*(sm->activeScene->entities + i));
        e.loop();
    }
}
void render(SDL_Renderer* renderer){
    for(int i = 0; i < sm->activeScene->entityCount; i++){
        Entity e = *(*(sm->activeScene->entities + i));
        e.render(renderer);
    }
}
void destroy(){
    for(int i = 0; i < sm->activeScene->entityCount; i++){
        Entity e = *(*(sm->activeScene->entities + i));
        e.destroy();
    }
}