#include "bas.h"
#include <SDL3/SDL_scancode.h>
#include "basanim.h"
#include "../entity.h"

Fighter bas;

void bas_skill1(Entity* fighter);
void bas_skill2(Entity* fighter);
void bas_skill3(Entity* fighter, int direction);
void bas_ultimate(Entity* fighter);

void bas_init() {
    bas.id = 1;
    bas.speed = 9.5f;
    bas.lightAttackTime = 0.28f;
    bas.heavyAttackTime = 0.55f;
    bas.crouchLightAttackTime = 0.35f;
    bas.crouchHeavyAttackTime = 0.65f;
    bas.fighterAnim = basAnim;

    bas.skill1 = &bas_skill1;
    bas.skill1Keys[0] = SDL_SCANCODE_K;
    bas.skill1Keys[1] = SDL_SCANCODE_J;
    bas.skill1Keys[2] = SDL_SCANCODE_K;
    bas.skill1Keys[3] = SDL_SCANCODE_J;

    bas.skill2 = &bas_skill2;
    bas.skill2Keys[0] = SDL_SCANCODE_J;
    bas.skill2Keys[1] = SDL_SCANCODE_J;
    bas.skill2Keys[2] = SDL_SCANCODE_J;
    bas.skill2Keys[3] = SDL_SCANCODE_K;

    bas.skill3 = &bas_skill3;
    bas.skill3Keys[0] = SDL_SCANCODE_K;
    bas.skill3Keys[1] = SDL_SCANCODE_K;
    bas.skill3Keys[2] = SDL_SCANCODE_K;
    bas.skill3Keys[3] = SDL_SCANCODE_J;

    bas.ultimate = &bas_ultimate;
}

void bas_skill1(Entity* fighter) {}
void bas_skill2(Entity* fighter) {}
void bas_skill3(Entity* fighter, int direction) {}
void bas_ultimate(Entity* fighter) {}