#include "menuscene.h"
#include "../scene.h"
#include "../entity.h"
#include "../entities/myentity.h"
#include "../entities/startbutton.h"

#include <stdio.h>

void menuscene_load();
void menuscene_unload();

void menuscene_init()
{
    menuscene = create_scene(&menuscene_load, &menuscene_unload);
}

void menuscene_load(){
    startbutton_init();
    add_entity(menuscene, startbutton);
}

void menuscene_unload(){
    remove_entity(menuscene, startbutton);
    startbutton->destroy();
}