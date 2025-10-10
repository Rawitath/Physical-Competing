#include "anotherscene.h"
#include "../scene.h"
#include "../entity.h"
#include "../entities/myentity.h"

#include <stdio.h>

void anotherscene_load();
void anotherscene_unload();

void anotherscene_init()
{
    anotherscene = create_scene(&anotherscene_load, &anotherscene_unload);
}

void anotherscene_load(){
    myentity_init();    
    add_entity(anotherscene, myentity);
    anotherscene->viewportZoom = 30.7;
}

void anotherscene_unload(){
    remove_entity(anotherscene, myentity);
    myentity->destroy();
}