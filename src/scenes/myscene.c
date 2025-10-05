#include "../scene.h"
#include "myscene.h"
#include "../entity.h"
#include "../entities/myentity.h"
#include "../entities/mytext.h"

void myscene_init()
{
    myscene = create_scene();
    
    myentity_init();
    mytext_init();
    
    add_entity(myscene, myentity);
    add_entity(myscene, mytext);
    myscene->viewportZoom = 70;
}