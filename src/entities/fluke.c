#include "fluke.h"
#include <SDL3/SDL_scancode.h>
#include "flukeanim.h"
#include "playerinput.h"
#include <stdio.h>
#include "drill.h"
#include "../entity.h"
#include "../scene.h"

Fighter fluke;

void fluke_skill1(Entity* fighter);
void fluke_skill2(Entity* fighter);
void fluke_skill3(Entity* fighter, int direction);
void fluke_ultimate(Entity* fighter);

void fluke_init() {
    fluke.id = 0;
    fluke.speed = 9.0f;
    fluke.lightAttackTime = 0.3f;
    fluke.heavyAttackTime = 0.6f;
    fluke.crouchLightAttackTime = 0.4f;
    fluke.crouchHeavyAttackTime = 0.7f;
    fluke.fighterAnim = flukeAnim;

    fluke.skill1 = &fluke_skill1;
    fluke.skill1Time = 4;
    fluke.skill1Keys[0] = INPUT_JUMP;
    fluke.skill1Keys[1] = INPUT_JUMP;
    fluke.skill1Keys[2] = INPUT_LIGHT;
    fluke.skill1Keys[3] = INPUT_HEAVY;

    fluke.skill2 = &fluke_skill2;
    fluke.skill2Time = 5;
    fluke.skill2Keys[0] = INPUT_LIGHT;
    fluke.skill2Keys[1] = INPUT_LIGHT;
    fluke.skill2Keys[2] = INPUT_LIGHT;
    fluke.skill2Keys[3] = INPUT_JUMP;

    fluke.skill3 = &fluke_skill3;
    fluke.skill3Time = 3.5;
    fluke.skill3Keys[0] = INPUT_LIGHT;
    fluke.skill3Keys[1] = INPUT_HEAVY;
    fluke.skill3Keys[2] = INPUT_HEAVY;
    fluke.skill3Keys[3] = INPUT_LIGHT;

    fluke.ultimate = &fluke_ultimate;
    fluke.ultimateTime = 6;

    // Initialize skill keys, skill function pointers, etc.
    // For example:
    // fluke.skill1Keys[0] = SDL_SCANCODE_J;
    // ...
    // fluke.skill1 = &fluke_skill1_function;
    // ...
}

void fluke_skill1(Entity* fighter){
    
}

void fluke_skill2(Entity* fighter)
{

}

void fluke_skill3(Entity* fighter, int direction)
{
    if(!drill) drill_init();
    add_entity(fighter->scene, drill);
    release_drill(fighter->x, fighter->y, direction);
}

void fluke_ultimate(Entity* fighter)
{
}
