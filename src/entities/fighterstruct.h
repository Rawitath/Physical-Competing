#ifndef FIGHTERSTRUCT_H
#define FIGHTERSTRUCT_H

#include <SDL3/SDL_scancode.h>
typedef struct FighterAnim FighterAnim;

typedef struct Fighter{
    int id;
    FighterAnim* fighterAnim;
    float speed;
    float lightAttackTime;
    float heavyAttackTime;
    float crouchLightAttackTime;
    float crouchHeavyAttackTime;
    float skill1Time;
    float skill2Time;
    float skill3Time;
    float ultimateTime;
    SDL_Scancode skill1Keys[4];
    SDL_Scancode skill2Keys[4];
    SDL_Scancode skill3Keys[4];
    void(*skill1)();
    void(*skill2)();
    void(*skill3)();
    void(*ultimate)();
} Fighter;

#endif // FIGHTERSTRUCT_H