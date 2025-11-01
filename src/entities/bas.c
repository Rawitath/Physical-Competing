#include "bas.h"
#include <SDL3/SDL_scancode.h>
#include "basanim.h"
#include "playerinput.h"
#include <stdio.h>

Fighter bas;

void bas_skill1();
void bas_skill2();
void bas_skill3();
void bas_ultimate();

void bas_init() {
    bas.id = 0;
    bas.speed = 9.0f;
    
    // Attack times
    bas.lightAttackTime = 0.3f;
    bas.heavyAttackTime = 0.6f;
    bas.crouchLightAttackTime = 0.4f;
    bas.crouchHeavyAttackTime = 0.7f;
    bas.skill1Time = 4;
    bas.skill2Time = 5;
    bas.skill3Time = 3.5;
    bas.ultimateTime = 6;
    
    // Attack damage (bas - Balanced fighter)
    bas.lightDamage = 5;
    bas.heavyDamage = 10;
    bas.crouchLightDamage = 4;
    bas.crouchHeavyDamage = 8;
    bas.skill1Damage = 15;      // มาตรฐาน
    bas.skill2Damage = 18;      // มาตรฐาน
    bas.skill3Damage = 20;      // มาตรฐาน
    bas.ultimateDamage = 35;    // มาตรฐาน
    
    // Attack ranges (bas - Medium range)
    bas.lightRange = 1.5f;
    bas.heavyRange = 1.8f;
    bas.crouchLightRange = 1.3f;
    bas.crouchHeavyRange = 1.5f;
    bas.skill1Range = 2.5f;     // มาตรฐาน
    bas.skill2Range = 2.5f;     // มาตรฐาน
    bas.skill3Range = 2.5f;     // มาตรฐาน
    bas.ultimateRange = 3.0f;   // มาตรฐาน
    
    bas.fighterAnim = basAnim;

    bas.skill1 = &bas_skill1;
    bas.skill1Keys[0] = INPUT_JUMP;
    bas.skill1Keys[1] = INPUT_JUMP;
    bas.skill1Keys[2] = INPUT_LIGHT;
    bas.skill1Keys[3] = INPUT_HEAVY;

    bas.skill2 = &bas_skill2;
    bas.skill2Keys[0] = INPUT_LIGHT;
    bas.skill2Keys[1] = INPUT_LIGHT;
    bas.skill2Keys[2] = INPUT_LIGHT;
    bas.skill2Keys[3] = INPUT_JUMP;

    bas.skill3 = &bas_skill3;
    bas.skill3Keys[0] = INPUT_LIGHT;
    bas.skill3Keys[1] = INPUT_HEAVY;
    bas.skill3Keys[2] = INPUT_HEAVY;
    bas.skill3Keys[3] = INPUT_LIGHT;

    bas.ultimate = &bas_ultimate;
}

void bas_skill1(){
    
}

void bas_skill2()
{

}

void bas_skill3()
{
}

void bas_ultimate()
{
}