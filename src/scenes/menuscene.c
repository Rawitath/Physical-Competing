#include "menuscene.h"
#include "../scene.h"
#include "../entity.h"
#include "../entities/myentity.h"
#include "../entities/mainmenu/menubg.h"
#include "../entities/mainmenu/startbutton.h"
#include "../entities/mainmenu/optionbutton.h"
#include "../entities/mainmenu/exitbutton.h"
#include "../entities/mainmenu/menuselector.h"
#include "../entities/mainmenu/menustate.h"

#include "../entities/selectionmenu/allbanner.h"
#include "../entities/selectionmenu/asiabanner.h"
#include "../entities/selectionmenu/basbanner.h"
#include "../entities/selectionmenu/flukebanner.h"
#include "../entities/selectionmenu/golfbanner.h"
#include "../entities/selectionmenu/p1select.h"
#include "../entities/selectionmenu/p2select.h"

#include <stdlib.h>

#include <stdio.h>

void menuscene_load();
void menuscene_unload();

void menuscene_init()
{
    menuscene = create_scene(&menuscene_load, &menuscene_unload);
}

void menuscene_load(){
    menustate_state = (int*)malloc(sizeof(int));
    *menustate_state = 0;
    startbutton_init();
    optionbutton_init();
    exitbutton_init();
    menuselector_init();
    menubg_init();

    flukebanner_init();
    basbanner_init();
    asiabanner_init();
    golfbanner_init();
    p1select_init();
    p2select_init();

    add_entity(menuscene, menubg);
    add_entity(menuscene, startbutton);
    add_entity(menuscene, optionbutton);
    add_entity(menuscene, exitbutton);
    add_entity(menuscene, menuselector);

    add_entity(menuscene, flukebanner);
    add_entity(menuscene, basbanner);
    add_entity(menuscene, asiabanner);
    add_entity(menuscene, golfbanner);
    add_entity(menuscene, p1select);
    add_entity(menuscene, p2select);

    allBanners[0] = flukebanner;
    allBanners[1] = basbanner;
    allBanners[2] = asiabanner;
    allBanners[3] = golfbanner;

}

void menuscene_unload(){
    remove_entity(menuscene, p1select);
    remove_entity(menuscene, p2select);
    remove_entity(menuscene, asiabanner);
    remove_entity(menuscene, flukebanner);
    remove_entity(menuscene, basbanner);
    remove_entity(menuscene, golfbanner);

    remove_entity(menuscene, menuselector);
    remove_entity(menuscene, exitbutton);
    remove_entity(menuscene, optionbutton);
    remove_entity(menuscene, startbutton);
    remove_entity(menuscene, menubg);

    p1select->destroy();
    p2select->destroy();
    flukebanner->destroy();
    basbanner->destroy();
    asiabanner->destroy();
    golfbanner->destroy();

    menuselector->destroy();
    exitbutton->destroy();
    optionbutton->destroy();
    startbutton->destroy();
    menubg->destroy();
    free(menustate_state);
}