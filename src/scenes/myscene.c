#include "../scene.h"
#include "myscene.h"
#include "../entity.h"
#include "../entities/myentity.h"
#include "../entities/mytext.h"

void myscene_load();
void myscene_unload();

void myscene_init()
{
    myscene = create_scene(&myscene_load, &myscene_unload);
}

void myscene_load(){
    myentity_init();
    mytext_init();
    
    add_entity(myscene, myentity);
    add_entity(myscene, mytext);
    myscene->viewportZoom = 70;
}

void myscene_unload(){
    remove_entity(myscene, myentity);
    remove_entity(myscene, mytext);
    myentity->destroy();
    mytext->destroy();
}