#include "../scene.h"
#include "myscene.h"
#include "../entity.h"
#include "../entities/myentity.h"
#include "../entities/soundtester.h"
#include "../entities/mytext.h"

void myscene_load();
void myscene_unload();

void myscene_init()
{
    myscene = create_scene(&myscene_load, &myscene_unload);
}

void myscene_load(){
    // myentity_init();
    mytext_init();
    soundtester_init();
    
    // add_entity(myscene, myentity);
    add_entity(myscene, mytext);
    add_entity(myscene, soundtester);
    myscene->viewportZoom = 70;
}

void myscene_unload(){
    remove_entity(myscene, soundtester);
    // remove_entity(myscene, myentity);
    remove_entity(myscene, mytext);
    soundtester->destroy();
    // myentity->destroy();
    mytext->destroy();
}