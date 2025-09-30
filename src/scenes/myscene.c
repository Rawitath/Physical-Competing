#include "../scene.h"
#include "myscene.h"
#include "../entity.h"
#include "../entities/myentity.h"

void myscene_init()
{
    myscene = create_scene();
    
    myentity_init();
    add_entity(myscene, myentity);
}