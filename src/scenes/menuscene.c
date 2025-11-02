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
#include "../entities/mainmenu/phycompetlogo.h"

#include "../entities/selectionmenu/allbanner.h"
#include "../entities/selectionmenu/asiabanner.h"
#include "../entities/selectionmenu/basbanner.h"
#include "../entities/selectionmenu/flukebanner.h"
#include "../entities/selectionmenu/golfbanner.h"
#include "../entities/selectionmenu/p1select.h"
#include "../entities/selectionmenu/p2select.h"
#include "../entities/selectionmenu/leftfighterdisplay.h"
#include "../entities/selectionmenu/rightfighterdisplay.h"
#include "../entities/selectionmenu/selectioncheck.h"
#include "../entities/selectionmenu/shadescreen.h"
#include "../entities/selectionmenu/leftnamedisplay.h"
#include "../entities/selectionmenu/rightnamedisplay.h"

#include "../entities/golfanim.h";
#include "../entities/flukeanim.h";
#include "../entities/basanim.h";
#include "../entities/asiaanim.h";
#include "../entities/fighteranim.h"

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

    golfAnim_init();
    flukeAnim_init();
    basAnim_init();
    asiaAnim_init();


    startbutton_init();
    // optionbutton_init();
    exitbutton_init();
    menuselector_init();
    menubg_init();
    phycompetlogo_init();

    flukebanner_init();
    basbanner_init();
    asiabanner_init();
    golfbanner_init();
    p1select_init();
    p2select_init();

    leftfighterdisplay_init();
    rightfighterdisplay_init();
    selectioncheck_init();
    shadescreen_init();

    leftnamedisplay_init();
    rightnamedisplay_init();

    add_entity(menuscene, menubg);
    add_entity(menuscene, startbutton);
    // add_entity(menuscene, optionbutton);
    add_entity(menuscene, exitbutton);
    add_entity(menuscene, menuselector);
    add_entity(menuscene, phycompetlogo);

    add_entity(menuscene, leftfighterdisplay);
    add_entity(menuscene, rightfighterdisplay);

    add_entity(menuscene, flukebanner);
    add_entity(menuscene, basbanner);
    add_entity(menuscene, asiabanner);
    add_entity(menuscene, golfbanner);
    add_entity(menuscene, p1select);
    add_entity(menuscene, p2select);
    add_entity(menuscene, selectioncheck);
    add_entity(menuscene, leftnamedisplay);
    add_entity(menuscene, rightnamedisplay);
    add_entity(menuscene, shadescreen);

    allBanners_size = 4;
    allBanners[0] = flukebanner;
    allBanners[1] = basbanner;
    allBanners[2] = asiabanner;
    allBanners[3] = golfbanner;
    allFighters[0] = flukeAnim;
    allFighters[1] = basAnim;
    allFighters[2] = asiaAnim;
    allFighters[3] = golfAnim;
}

void menuscene_unload(){
    remove_entity(menuscene, rightnamedisplay);
    remove_entity(menuscene, leftnamedisplay);
    remove_entity(menuscene, shadescreen);
    remove_entity(menuscene, selectioncheck);
    remove_entity(menuscene, leftfighterdisplay);
    remove_entity(menuscene, rightfighterdisplay);
    remove_entity(menuscene, p1select);
    remove_entity(menuscene, p2select);
    remove_entity(menuscene, asiabanner);
    remove_entity(menuscene, flukebanner);
    remove_entity(menuscene, basbanner);
    remove_entity(menuscene, golfbanner);

    remove_entity(menuscene, menuselector);
    remove_entity(menuscene, exitbutton);
    // remove_entity(menuscene, optionbutton);
    remove_entity(menuscene, startbutton);
    remove_entity(menuscene, phycompetlogo);
    remove_entity(menuscene, menubg);

    rightnamedisplay->destroy();
    leftnamedisplay->destroy();

    shadescreen->destroy();
    selectioncheck->destroy();
    leftfighterdisplay->destroy();
    rightfighterdisplay->destroy();

    p1select->destroy();
    p2select->destroy();
    flukebanner->destroy();
    basbanner->destroy();
    asiabanner->destroy();
    golfbanner->destroy();

    menuselector->destroy();
    exitbutton->destroy();
    // optionbutton->destroy();
    startbutton->destroy();
    phycompetlogo->destroy();
    menubg->destroy();
    free(menustate_state);

    destroy_fighteranim(flukeAnim);
    destroy_fighteranim(golfAnim);
    destroy_fighteranim(basAnim);
    destroy_fighteranim(asiaAnim);

}