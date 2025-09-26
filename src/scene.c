#include <stdlib.h>
#include "scene.h"
#include "entity.h"

void init_scene(Scene* scene, unsigned int id){
    //set id, init every value to 0, malloc space
    scene->id = id;
    scene->entityCount = 0;
    scene->entities = (Entity**)malloc(sizeof(Entity*));
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
        Entity** temp = (Entity**)realloc(scene->entities, scene->entityCount + 1 * sizeof(Entity*));
        scene->entities = temp;
    }

    *(scene->entities + scene->entityCount) = entity;
    scene->entityCount++;
    return ADD_ENTITY_SUCCESS;
}

int remove_entity(Scene *scene, Entity *entity){
    //find if entity is exist in scene
    for(int i = 0; i < scene->entityCount; i++){
        if(*(scene->entities + i) == entity){
            if(i != scene->entityCount - 1){
                for(int j = i; j < scene->entityCount - 1; j++){
                    *(scene->entities + j) = *(scene->entities + j + 1);
                }
            }

            Entity** temp = (Entity**)realloc(scene->entities, scene->entityCount - 1 * sizeof(Entity*));
            scene->entities = temp;
            scene->entityCount--;

            return REMOVE_ENTITY_SUCCESS;
        }
    }
    return REMOVE_ENTITY_NOT_EXIST;
}

Entity* get_entity_by_index(Scene* scene, int index){
    
}

void init_scene_manager(SceneManager* sm){
    //init every value to 0, malloc space
    sm->sceneCount = 0;
    sm->scenes = (Scene**)malloc(sizeof(Scene*));
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
        Scene** temp = (Scene**)realloc(sm->scenes, sm->sceneCount + 1 * sizeof(Scene*));
        scene->entities = temp;
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

            Scene** temp = (Scene**)realloc(sm->scenes, sm->sceneCount - 1 * sizeof(Scene*));
            sm->scenes = temp;
            sm->sceneCount--;

            return REMOVE_SCENE_SUCCESS;
        }
    }
    return REMOVE_SCENE_NOT_EXIST;
}