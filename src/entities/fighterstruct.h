#ifndef FIGHTERSTRUCT_H
#define FIGHTERSTRUCT_H

typedef enum PlayerInput PlayerInput;
typedef struct FighterAnim FighterAnim;
typedef struct Entity Entity;

typedef struct Fighter{
    int id;
    const char* name;
    FighterAnim* fighterAnim;
    float speed;
    
    // Attack times
    float lightAttackTime;
    float heavyAttackTime;
    float crouchLightAttackTime;
    float crouchHeavyAttackTime;
    float skill1Time;
    float skill2Time;
    float skill3Time;
    float ultimateTime;
    
    // Attack damage values
    int lightDamage;
    int heavyDamage;
    int crouchLightDamage;
    int crouchHeavyDamage;
    int skill1Damage;
    int skill2Damage;
    int skill3Damage;
    int ultimateDamage;
    
    // Attack ranges
    float lightRange;
    float heavyRange;
    float crouchLightRange;
    float crouchHeavyRange;
    float skill1Range;
    float skill2Range;
    float skill3Range;
    float ultimateRange;
    
    // Skill keys
    PlayerInput skill1Keys[4];
    PlayerInput skill2Keys[4];
    PlayerInput skill3Keys[4];
    void(*skill1)(Entity* fighter, int direction);
    void(*skill2)(Entity* fighter, int direction);
    void(*skill3)(Entity* fighter, int direction);
    void(*ultimate)(Entity* fighter);
} Fighter;

#endif // FIGHTERSTRUCT_H