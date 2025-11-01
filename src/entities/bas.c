#include "bas.h"
#include <SDL3/SDL_scancode.h>
#include "basanim.h"
#include "playerinput.h"

Fighter bas;

void bas_skill1();
void bas_skill2();
void bas_skill3();
void bas_ultimate();

void bas_init() {
    bas.id = 1;
    bas.speed = 9.5f;
    bas.lightAttackTime = 0.28f;
    bas.heavyAttackTime = 0.55f;
    bas.crouchLightAttackTime = 0.35f;
    bas.crouchHeavyAttackTime = 0.65f;
    bas.fighterAnim = basAnim;

    bas.skill1 = &bas_skill1;
    bas.skill1Keys[0] = INPUT_HEAVY;
    bas.skill1Keys[1] = INPUT_LIGHT;
    bas.skill1Keys[2] = INPUT_HEAVY;
    bas.skill1Keys[3] = INPUT_LIGHT;

    bas.skill2 = &bas_skill2;
    bas.skill2Keys[0] = INPUT_LIGHT;
    bas.skill2Keys[1] = INPUT_LIGHT;
    bas.skill2Keys[2] = INPUT_LIGHT;
    bas.skill2Keys[3] = INPUT_HEAVY;

    bas.skill3 = &bas_skill3;
    bas.skill3Keys[0] = INPUT_HEAVY;
    bas.skill3Keys[1] = INPUT_HEAVY;
    bas.skill3Keys[2] = INPUT_HEAVY;
    bas.skill3Keys[3] = INPUT_LIGHT;

    bas.ultimate = &bas_ultimate;
}

void bas_skill1() {}
void bas_skill2() {}
void bas_skill3() {}
void bas_ultimate() {}