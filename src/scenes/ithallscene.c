#include "ithallscene.h"
#include "../scene.h"
#include "../entity.h"
#include "../entities/ithallstage.h"
#include "../entities/timecounter.h"
#include "../entities/wintext.h"
#include "../entities/lefthealthbar.h"
#include "../entities/righthealthbar.h"
#include "../entities/leftultibar.h"
#include "../entities/rightultibar.h"
#include "../entities/rightbanner.h"
#include "../entities/leftbanner.h"
#include "../entities/stageui.h"

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
    lefthealthbar_init();
    righthealthbar_init();
    rightbanner_init();
    leftbanner_init();
    stageui_init();
    leftultibar_init();
    rightultibar_init();

    add_entity(ithallscene, ithallstage);

    add_entity(ithallscene, rightbanner);
    add_entity(ithallscene, leftbanner);

    add_entity(ithallscene, stageui);

    add_entity(ithallscene, timecounter);
    add_entity(ithallscene, wintext);
    add_entity(ithallscene, lefthealthbar);
    add_entity(ithallscene, righthealthbar);
    add_entity(ithallscene, leftultibar);
    add_entity(ithallscene, rightultibar);

    

    ithallscene->viewportY = -2;
    ithallscene->viewportZoom = 60;
}

void ithallscene_unload(){
    remove_entity(ithallscene, stageui);
    remove_entity(ithallscene, rightbanner);
    remove_entity(ithallscene, leftbanner);
    add_entity(ithallscene, leftultibar);
    add_entity(ithallscene, rightultibar);
    remove_entity(ithallscene, lefthealthbar);
    remove_entity(ithallscene, righthealthbar);
    remove_entity(ithallscene, wintext);
    remove_entity(ithallscene, timecounter);
    remove_entity(ithallscene, ithallstage);
    leftultibar->destroy();
    rightultibar->destroy();
    stageui->destroy();
    rightbanner->destroy();
    leftbanner->destroy();
    lefthealthbar->destroy();
    righthealthbar->destroy();
    wintext->destroy();
    timecounter->destroy();
    ithallstage->destroy();
}