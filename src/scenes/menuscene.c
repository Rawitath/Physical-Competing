#include "menuscene.h"
#include "../scene.h"
#include "../entity.h"
#include "../entities/myentity.h"
#include "../entities/startbutton.h"
#include "../entities/optionbutton.h"
#include "../entities/exitbutton.h"
#include "../entities/menuselector.h"

#include <stdio.h>

void menuscene_load();
void menuscene_unload();

void menuscene_init()
{
    menuscene = create_scene(&menuscene_load, &menuscene_unload);
}

void menuscene_load(){
    startbutton_init();
    optionbutton_init();
    exitbutton_init();
    menuselector_init();

    add_entity(menuscene, startbutton);
    add_entity(menuscene, optionbutton);
    add_entity(menuscene, exitbutton);
    add_entity(menuscene, menuselector);

}

void menuscene_unload(){
    remove_entity(menuscene, menuselector);
    remove_entity(menuscene, exitbutton);
    remove_entity(menuscene, optionbutton);
    remove_entity(menuscene, startbutton);

    menuselector->destroy();
    exitbutton->destroy();
    optionbutton->destroy();
    startbutton->destroy();
}