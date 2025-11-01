#include "golf.h"
#include <SDL3/SDL_scancode.h>
#include "golfanim.h"
#include "playerinput.h"

Fighter golf;

void golf_skill1();
void golf_skill2();
void golf_skill3();
void golf_ultimate();

void golf_init() {
    golf.id = 3;
    golf.speed = 8.5f;
    golf.lightAttackTime = 0.35f;
    golf.heavyAttackTime = 0.65f;
    golf.crouchLightAttackTime = 0.45f;
    golf.crouchHeavyAttackTime = 0.75f;
    golf.fighterAnim = golfAnim;

    golf.skill1 = &golf_skill1;
    golf.skill1Keys[0] = INPUT_LIGHT;
    golf.skill1Keys[1] = INPUT_LIGHT;
    golf.skill1Keys[2] = INPUT_LIGHT;
    golf.skill1Keys[3] = INPUT_LIGHT;

    golf.skill2 = &golf_skill2;
    golf.skill2Keys[0] = INPUT_HEAVY;
    golf.skill2Keys[1] = INPUT_HEAVY;
    golf.skill2Keys[2] = INPUT_HEAVY;
    golf.skill2Keys[3] = INPUT_HEAVY;

    golf.skill3 = &golf_skill3;
    golf.skill3Keys[0] = INPUT_LIGHT;
    golf.skill3Keys[1] = INPUT_HEAVY;
    golf.skill3Keys[2] = INPUT_HEAVY;
    golf.skill3Keys[3] = INPUT_LIGHT;

    golf.ultimate = &golf_ultimate;
}

void golf_skill1() {}
void golf_skill2() {}
void golf_skill3() {}
void golf_ultimate() {}