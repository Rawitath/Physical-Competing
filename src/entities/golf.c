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
    
    // Attack times
    golf.lightAttackTime = 0.35f;
    golf.heavyAttackTime = 0.65f;
    golf.crouchLightAttackTime = 0.45f;
    golf.crouchHeavyAttackTime = 0.75f;
    golf.skill1Time = 6;
    golf.skill2Time = 5.5;
    golf.skill3Time = 6.5;
    golf.ultimateTime = 8;
    
    // Attack damage (Golf - Tank/Defense fighter with moderate damage)
    golf.lightDamage = 5;
    golf.heavyDamage = 10;
    golf.crouchLightDamage = 4;
    golf.crouchHeavyDamage = 8;
    golf.skill1Damage = 18;       // ปานกลาง-สูง
    golf.skill2Damage = 16;       // ปานกลาง
    golf.skill3Damage = 22;       // สูง
    golf.ultimateDamage = 38;     // สูงมาก!
    
    // Attack ranges (Golf - Medium-long range tank)
    golf.lightRange = 1.6f;
    golf.heavyRange = 1.9f;
    golf.crouchLightRange = 1.4f;
    golf.crouchHeavyRange = 1.6f;
    golf.skill1Range = 2.7f;      // ไกลกว่ามาตรฐาน
    golf.skill2Range = 2.4f;      // ใกล้มาตรฐาน
    golf.skill3Range = 2.6f;      // ไกลกว่ามาตรฐาน
    golf.ultimateRange = 3.2f;    // ไกล
    
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