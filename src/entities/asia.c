#include "asia.h"
#include <SDL3/SDL_scancode.h>
#include "playerinput.h"

Fighter asia;

void asia_skill1();
void asia_skill2();
void asia_skill3();
void asia_ultimate();

void asia_init() {
    asia.id = 2;
    asia.speed = 10.0f;
    asia.lightAttackTime = 0.25f;
    asia.heavyAttackTime = 0.5f;
    asia.crouchLightAttackTime = 0.3f;
    asia.crouchHeavyAttackTime = 0.6f;

    asia.skill1 = &asia_skill1;
    asia.skill1Keys[0] = INPUT_LIGHT;
    asia.skill1Keys[1] = INPUT_LIGHT;
    asia.skill1Keys[2] = INPUT_HEAVY;
    asia.skill1Keys[3] = INPUT_JUMP;

    asia.skill2 = &asia_skill2;
    asia.skill2Keys[0] = INPUT_JUMP;
    asia.skill2Keys[1] = INPUT_JUMP;
    asia.skill2Keys[2] = INPUT_LIGHT;
    asia.skill2Keys[3] = INPUT_HEAVY;

    asia.skill3 = &asia_skill3;
    asia.skill3Keys[0] = INPUT_LIGHT;
    asia.skill3Keys[1] = INPUT_LIGHT;
    asia.skill3Keys[2] = INPUT_LIGHT;
    asia.skill3Keys[3] = INPUT_LIGHT;

    asia.ultimate = &asia_ultimate;
}

void asia_skill1() {}
void asia_skill2() {}
void asia_skill3() {}
void asia_ultimate() {}