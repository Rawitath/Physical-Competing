#include "asia.h"
#include <SDL3/SDL_scancode.h>
#include "asiaanim.h"
#include "playerinput.h"
#include <stdio.h>

Fighter asia;

void asia_skill1();
void asia_skill2();
void asia_skill3();
void asia_ultimate();

void asia_init() {
    asia.id = 0;
    asia.speed = 9.0f;
    
    // Attack times
    asia.lightAttackTime = 0.3f;
    asia.heavyAttackTime = 0.6f;
    asia.crouchLightAttackTime = 0.4f;
    asia.crouchHeavyAttackTime = 0.7f;
    asia.skill1Time = 4;
    asia.skill2Time = 5;
    asia.skill3Time = 3.5;
    asia.ultimateTime = 6;
    
    // Attack damage (asia - Balanced fighter)
    asia.lightDamage = 5;
    asia.heavyDamage = 10;
    asia.crouchLightDamage = 4;
    asia.crouchHeavyDamage = 8;
    asia.skill1Damage = 15;      // มาตรฐาน
    asia.skill2Damage = 18;      // มาตรฐาน
    asia.skill3Damage = 20;      // มาตรฐาน
    asia.ultimateDamage = 35;    // มาตรฐาน
    
    // Attack ranges (asia - Medium range)
    asia.lightRange = 1.5f;
    asia.heavyRange = 1.8f;
    asia.crouchLightRange = 1.3f;
    asia.crouchHeavyRange = 1.5f;
    asia.skill1Range = 2.5f;     // มาตรฐาน
    asia.skill2Range = 2.5f;     // มาตรฐาน
    asia.skill3Range = 2.5f;     // มาตรฐาน
    asia.ultimateRange = 3.0f;   // มาตรฐาน
    
    asia.fighterAnim = asiaAnim;

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

void asia_skill1(){
    
}

void asia_skill2()
{

}

void asia_skill3()
{
}

void asia_ultimate()
{
}