#include "ithallscene.h"
#include "../scene.h"
#include "../entity.h"
#include "../entities/myentity.h"

#include <stdio.h>

void ithallscene_load();
void ithallscene_unload();

void ithallscene_init()
{
    ithallscene = create_scene(&ithallscene_load, &ithallscene_unload);
}

void ithallscene_load(){

}

void ithallscene_unload(){
    
}