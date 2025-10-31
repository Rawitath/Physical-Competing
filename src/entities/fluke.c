#include "fluke.h"
#include <SDL3/SDL_scancode.h>
#include "flukeanim.h"

Fighter fluke;

void fluke_skill1();
void fluke_skill2();
void fluke_skill3();
void fluke_ultimate();

void fluke_init() {
    fluke.id = 2; // Example ID
    fluke.speed = 9.0f;
    fluke.lightAttackTime = 0.3f;
    fluke.heavyAttackTime = 0.6f;
    fluke.crouchLightAttackTime = 0.4f;
    fluke.crouchHeavyAttackTime = 0.7f;
    fluke.fighterAnim = flukeAnim;

    fluke.skill1 = &fluke_skill1;
    fluke.skill1Keys[0] = SDL_SCANCODE_J;
    fluke.skill1Keys[1] = SDL_SCANCODE_K;
    fluke.skill1Keys[2] = SDL_SCANCODE_K;
    fluke.skill1Keys[3] = SDL_SCANCODE_J;

    fluke.skill2 = &fluke_skill2;
    fluke.skill2Keys[0] = SDL_SCANCODE_J;
    fluke.skill2Keys[1] = SDL_SCANCODE_K;
    fluke.skill2Keys[2] = SDL_SCANCODE_K;
    fluke.skill2Keys[3] = SDL_SCANCODE_J;

    fluke.skill3 = &fluke_skill3;
    fluke.skill3Keys[0] = SDL_SCANCODE_J;
    fluke.skill3Keys[1] = SDL_SCANCODE_K;
    fluke.skill3Keys[2] = SDL_SCANCODE_K;
    fluke.skill3Keys[3] = SDL_SCANCODE_J;

    fluke.ultimate = &fluke_ultimate;

    // Initialize skill keys, skill function pointers, etc.
    // For example:
    // fluke.skill1Keys[0] = SDL_SCANCODE_J;
    // ...
    // fluke.skill1 = &fluke_skill1_function;
    // ...
}

void fluke_skill1(){

}

void fluke_skill2()
{
    
}

void fluke_skill3()
{
}

void fluke_ultimate()
{
}
