#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "scene.h"
#include "entity.h"

Scene* create_scene(void (*load)(), void (*unload)()){
    //init every value to 0, malloc space
    Scene* scene = (Scene*)malloc(sizeof(Scene));
    scene->entityCount = 0;
    scene->entities = (Entity**)malloc(sizeof(Entity*));
    scene->viewportX = 0.0;
    scene->viewportY = 0.0;
    scene->viewportZoom = 1.0;

    scene->load = load;
    scene->unload = unload;

    return scene;
}

int add_entity(Scene *scene, Entity *entity){

    //find if entity is already with the same address exist in scene
    for(int i = 0; i < scene->entityCount; i++){
        if(*(scene->entities + i) == entity){
            return ADD_ENTITY_ALREADY_EXIST;
        }
    }
    //resize the Entity**
    if(scene->entityCount > 0){
        Entity** temp = (Entity**)realloc(scene->entities, (scene->entityCount + 1) * sizeof(Entity*));
        if(temp == NULL){
            return ADD_ENTITY_ALLOCATION_FAILED;
        }
        scene->entities = temp;
    }

    *(scene->entities + scene->entityCount) = entity;
    scene->entityCount++;

    entity->scene = scene;

    return ADD_ENTITY_SUCCESS;
}

int remove_entity(Scene *scene, Entity *entity){
    //find if entity is exist in scene
    for(int i = 0; i < scene->entityCount; i++){
        if(*(scene->entities + i) == entity){

            entity->scene = NULL;

            if(i != scene->entityCount - 1){
                for(int j = i; j < scene->entityCount - 1; j++){
                    *(scene->entities + j) = *(scene->entities + j + 1);
                }
            }
            // 1 == 0 return 0 when scene->entityCount is not 0 otherwise, 1
            Entity** temp = (Entity**)realloc(scene->entities, (scene->entityCount - (1 == 0)) * sizeof(Entity*));
            if(temp == NULL){
                return REMOVE_ENTITY_ALLOCATION_FAILED;
            }
            scene->entities = temp;
            scene->entityCount--;

            return REMOVE_ENTITY_SUCCESS;
        }
    }
    return REMOVE_ENTITY_NOT_EXIST;
}

Entity* get_entity_by_index(Scene* scene, int index){
    if(index < 0 || index >= scene->entityCount){
        return GET_ENTITY_OUT_OF_BOUND;
    }
    return *(scene->entities + index);
}

Entity *get_entity_by_id(Scene *scene, int id)
{
    for(int i = 0; i < scene->entityCount; i++){
        Entity* e = get_entity_by_index(scene, i);
        if(e->id == id){
            return e;
        }
    }
    return GET_ENTITY_NOT_FOUND;
}

Entity *get_entity_by_name(Scene *scene, const char *name)
{
    for(int i = 0; i < scene->entityCount; i++){
        Entity* e = get_entity_by_index(scene, i);
        if(strcmp(e->name, name) == 0){
            return e;
        }
    }
    return GET_ENTITY_NOT_FOUND;
}

void destroy_scene(Scene *scene)
{
    free(scene->entities);
    free(scene);
}

SceneManager* create_scene_manager(){
    SceneManager* sm = (SceneManager*)malloc(sizeof(SceneManager));
    sm->sceneCount = 0;
    sm->scenes = (Scene**)malloc(sizeof(Scene*));
    sm->activeScene = NULL;
    return sm;
}

int add_scene(SceneManager* sm, Scene* scene){
    //find if scene is already with the same address exist in scene manager
    for(int i = 0; i < sm->sceneCount; i++){
        if(*(sm->scenes + i) == scene){
            return ADD_SCENE_ALREADY_EXIST;
        }
    }

    //resize the Scene**
    if(sm->sceneCount > 0){
        Scene** temp = (Scene**)realloc(sm->scenes, (sm->sceneCount + 1) * sizeof(Scene*));
        if(temp == NULL){
            return ADD_SCENE_ALLOCATION_FAILED;
        }
        sm->scenes = temp;
    }

    *(sm->scenes + sm->sceneCount) = scene;
    sm->sceneCount++;
    return ADD_SCENE_SUCCESS;
}
int remove_scene(SceneManager* sm, Scene* scene){
    //find if scene is exist in scene manager
    for(int i = 0; i < sm->sceneCount; i++){
        if(*(sm->scenes + i) == scene){
            if(i != sm->sceneCount - 1){
                for(int j = i; j < sm->sceneCount - 1; j++){
                    *(sm->scenes + j) = *(sm->scenes + j + 1);
                }
            }

            Scene** temp = (Scene**)realloc(sm->scenes, (sm->sceneCount - 1) * sizeof(Scene*));
            if(temp == NULL){
                return REMOVE_SCENE_ALLOCATION_FAILED;
            }
            sm->scenes = temp;
            sm->sceneCount--;

            return REMOVE_SCENE_SUCCESS;
        }
    }
    return REMOVE_SCENE_NOT_EXIST;
}

Scene *get_scene_by_index(SceneManager *sm, int index)
{
    if(index < 0 || index >= sm->sceneCount){
        return GET_SCENE_OUT_OF_BOUND;
    }
    return *(sm->scenes + index);
}

Scene *get_scene_by_id(SceneManager *sm, int id)
{
    for(int i = 0; i < sm->sceneCount; i++){
        Scene* s = get_scene_by_index(sm, i);
        if(s->id == id){
            return s;
        }
    }
    return GET_SCENE_NOT_FOUND;
}

Scene *get_scene_by_name(SceneManager *sm, const char *name)
{
    for(int i = 0; i < sm->sceneCount; i++){
        Scene* s = get_scene_by_index(sm, i);
        if(strcmp(s->name, name)){
            return s;
        }
    }
    return GET_SCENE_NOT_FOUND;
}

void destroy_scene_manager(SceneManager *sm)
{
    free(sm->scenes);
    free(sm);
}

int load_scene(SceneManager *sm, int index)
{
    Scene* scene = get_scene_by_index(sm, index);
    if(scene == NULL){
        return LOAD_SCENE_OUT_OF_BOUND;
    }
    if(sm->activeScene != NULL){
        sm->activeScene->unload();
        sm->activeScene = NULL;
    }
    scene->load();
    sm->activeScene = scene;
    return LOAD_SCENE_SUCCESS;
}
