#include "ithallscene.h"
#include "../scene.h"
#include "../entity.h"
#include "../entities/ithallstage.h"
#include "../entities/timecounter.h"
#include "../entities/wintext.h"

#include <stdio.h>

void ithallscene_load();
void ithallscene_unload();

void ithallscene_init()
{
    ithallscene = create_scene(&ithallscene_load, &ithallscene_unload);
}

void ithallscene_load(){
    ithallstage_init();
    timecounter_init();
    wintext_init();

    add_entity(ithallscene, ithallstage);
    add_entity(ithallscene, timecounter);
    add_entity(ithallscene, wintext);

    ithallscene->viewportY = 3;
    ithallscene->viewportZoom = 60;
}

void ithallscene_unload(){
    remove_entity(ithallscene, wintext);
    remove_entity(ithallscene, timecounter);
    remove_entity(ithallscene, ithallstage);
    wintext->destroy();
    timecounter->destroy();
    ithallstage->destroy();
}