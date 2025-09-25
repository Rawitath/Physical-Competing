#include <stdlib.h>

#include "scene.h"
#include "entity.h"

void init_scene(Scene* scene, unsigned int id){
    scene->id = id;
    scene->entityCount = 0;
    scene->entities = (Entity**)malloc(sizeof(Entity*));
}

int add_entity(Scene *scene, Entity *entity){
    for(int i = 0; i < scene->entityCount; i++){
        if(*(scene->entities + i) == entity){
            return ADD_ENTITY_ALREADY_EXIST;
        }
    }

    if(scene->entityCount > 0){
        Entity** temp = (Entity**)realloc(scene->entities, scene->entityCount + 1 * sizeof(Entity*));
        scene->entities = temp;
    }

    *(scene->entities + scene->entityCount) = entity;
    scene->entityCount++;
    return ADD_ENTITY_SUCCESS;
}

int remove_entity(Scene *scene, Entity *entity){
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
