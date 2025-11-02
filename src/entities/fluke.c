#include "fluke.h"
#include <SDL3/SDL_scancode.h>
#include "flukeanim.h"
#include "playerinput.h"
#include <stdio.h>
#include "drill.h"
#include "../entity.h"
#include "../scene.h"

Fighter fluke;

void fluke_skill1(Entity* fighter, int direction);
void fluke_skill2(Entity* fighter, int direction);
void fluke_skill3(Entity* fighter, int direction);
void fluke_ultimate();

void fluke_init() {
    fluke.id = 0;
    fluke.speed = 9.0f;
    fluke.name = "Nerd";
    
    // Attack times
    fluke.lightAttackTime = 1.5f;
    fluke.heavyAttackTime = 1.8f;
    fluke.crouchLightAttackTime = 1.5f;
    fluke.crouchHeavyAttackTime = 1.8f;
    fluke.skill1Time = 4;
    fluke.skill2Time = 5;
    fluke.skill3Time = 3.5;
    fluke.ultimateTime = 6;
    
    // Attack damage (Fluke - Balanced fighter)
    fluke.lightDamage = 5;
    fluke.heavyDamage = 10;
    fluke.crouchLightDamage = 4;
    fluke.crouchHeavyDamage = 8;
    fluke.skill1Damage = 15;      // มาตรฐาน
    fluke.skill2Damage = 18;      // มาตรฐาน
    fluke.skill3Damage = 20;      // มาตรฐาน
    fluke.ultimateDamage = 35;    // มาตรฐาน
    
    // Attack ranges (Fluke - Medium range)
    fluke.lightRange = 4.2f;
    fluke.heavyRange = 3.8f;
    fluke.crouchLightRange = 3.0f;
    fluke.crouchHeavyRange = 3.5f;
    fluke.skill1Range = 4.0f;     // มาตรฐาน
    fluke.skill2Range = 2.5f;     // มาตรฐาน
    fluke.skill3Range = 2.0f;     // มาตรฐาน
    fluke.ultimateRange = 3.0f;   // มาตรฐาน
    
    fluke.fighterAnim = flukeAnim;

    fluke.skill1 = &fluke_skill1;
    fluke.skill1Keys[0] = INPUT_JUMP;
    fluke.skill1Keys[1] = INPUT_JUMP;
    fluke.skill1Keys[2] = INPUT_LIGHT;
    fluke.skill1Keys[3] = INPUT_HEAVY;

    fluke.skill2 = &fluke_skill2;
    fluke.skill2Keys[0] = INPUT_LIGHT;
    fluke.skill2Keys[1] = INPUT_LIGHT;
    fluke.skill2Keys[2] = INPUT_LIGHT;
    fluke.skill2Keys[3] = INPUT_JUMP;

    fluke.skill3 = &fluke_skill3;
    fluke.skill3Keys[0] = INPUT_LIGHT;
    fluke.skill3Keys[1] = INPUT_HEAVY;
    fluke.skill3Keys[2] = INPUT_HEAVY;
    fluke.skill3Keys[3] = INPUT_LIGHT;

    fluke.ultimate = &fluke_ultimate;
}

void fluke_skill1(Entity* fighter, int direction){
    
}

void fluke_skill2(Entity* fighter, int direction)
{

}

void fluke_skill3(Entity* fighter, int direction)
{
    if(!drill) drill_init();
    add_entity(fighter->scene, drill);
    release_drill(fighter, direction);
}

void fluke_ultimate()
{
}