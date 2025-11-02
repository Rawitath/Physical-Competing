#include "asia.h"
#include <SDL3/SDL_scancode.h>
#include "../entity.h"
#include "bottle.h"
#include "../scene.h"
#include "asiaanim.h"
#include "playerinput.h"
#include <stdio.h>
#include <math.h>
#include "characterstate.h"

Fighter asia;

void asia_skill1(Entity* fighter, int direction);
void asia_skill2(Entity* fighter, int direction);
void asia_skill3(Entity* fighter, int direction);
void asia_ultimate(Entity* fighter);

// Ultimate hit tracking
typedef struct {
    int active;
    int hitCount;
    float hitTimer;
    float hitInterval;
    int totalHits;
    int damagePerHit;
    float range;
} UltimateState;

static UltimateState leftAsia_ultimate = {0};
static UltimateState rightAsia_ultimate = {0};

void asia_init() {
    asia.id = 0;
    asia.speed = 9.0f;
    
    // Attack times
    asia.lightAttackTime = 0.3f;
    asia.heavyAttackTime = 0.6f;
    asia.crouchLightAttackTime = 0.4f;
    asia.crouchHeavyAttackTime = 0.7f;
    asia.skill1Time = 4;
    asia.skill2Time = 2.5;
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
    asia.ultimateDamage = 30;    // 10 damage per hit × 3 hits
    
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
    asia.skill1Time = 4;
    asia.skill1Keys[0] = INPUT_LIGHT;
    asia.skill1Keys[1] = INPUT_LIGHT;
    asia.skill1Keys[2] = INPUT_HEAVY;
    asia.skill1Keys[3] = INPUT_JUMP;

    asia.skill2 = &asia_skill2;
    asia.skill2Time = 5;
    asia.skill2Keys[0] = INPUT_JUMP;
    asia.skill2Keys[1] = INPUT_JUMP;
    asia.skill2Keys[2] = INPUT_LIGHT;
    asia.skill2Keys[3] = INPUT_HEAVY;

    asia.skill3 = &asia_skill3;
    asia.skill3Time = 3.5;
    asia.skill3Keys[0] = INPUT_LIGHT;
    asia.skill3Keys[1] = INPUT_LIGHT;
    asia.skill3Keys[2] = INPUT_LIGHT;
    asia.skill3Keys[3] = INPUT_LIGHT;

    asia.ultimate = &asia_ultimate;
    asia.ultimateTime = 6;
}

//drink
void asia_skill1(Entity* fighter, int direction) {}
//throw
void asia_skill2(Entity* fighter, int direction) {
    if(!bottle) bottle_init();
    add_entity(fighter->scene, bottle);
    release_bottle(fighter->x, fighter->y, direction);
}
// hit
void asia_skill3(Entity* fighter, int direction) {}

// Check if target is in range
int asia_is_in_ultimate_range(float attacker_x, float target_x, float range) {
    return fabsf(target_x - attacker_x) <= range;
}

void asia_ultimate(Entity* fighter) {
    // Determine which fighter this is (left or right)
    extern Entity* leftFighter;
    extern Entity* rightFighter;
    
    UltimateState* state = NULL;
    
    if (fighter == leftFighter) {
        state = &leftAsia_ultimate;
    } else if (fighter == rightFighter) {
        state = &rightAsia_ultimate;
    }
    
    if (state) {
        // Initialize ultimate state
        state->active = 1;
        state->hitCount = 0;
        state->hitTimer = 0.0f;
        state->hitInterval = 0.4f;  // 0.4 seconds between each hit
        state->totalHits = 3;        // 3 hits total
        state->damagePerHit = 11;    // 10 damage per hit (30 total)
        state->range = asia.ultimateRange;
    }
}

// This function should be called in the main game loop (fightcontroller)
void asia_ultimate_update() {
    extern Entity* leftFighter;
    extern Entity* rightFighter;
    extern CharacterState leftFighter_currentState;
    extern CharacterState rightFighter_currentState;
    
    float delta = get_delta();
    
    // Update left fighter's ultimate
    if (leftAsia_ultimate.active) {
        leftAsia_ultimate.hitTimer += delta;
        
        // Check if it's time for the next hit
        if (leftAsia_ultimate.hitTimer >= leftAsia_ultimate.hitInterval) {
            leftAsia_ultimate.hitTimer = 0.0f;
            
            // Check if target is in range
            if (asia_is_in_ultimate_range(leftFighter->x, rightFighter->x, leftAsia_ultimate.range)) {
                // Deal damage
                rightFighter_subtract_health(leftAsia_ultimate.damagePerHit);
                leftFighter_add_ultimate(leftAsia_ultimate.damagePerHit / 3);
            }
            
            leftAsia_ultimate.hitCount++;
            
            // Check if we've done all hits
            if (leftAsia_ultimate.hitCount >= leftAsia_ultimate.totalHits) {
                leftAsia_ultimate.active = 0;
            }
        }
        
        // Deactivate if no longer in ultimate state
        if (leftFighter_currentState != STATE_ULTIMATE) {
            leftAsia_ultimate.active = 0;
        }
    }
    
    // Update right fighter's ultimate
    if (rightAsia_ultimate.active) {
        rightAsia_ultimate.hitTimer += delta;
        
        // Check if it's time for the next hit
        if (rightAsia_ultimate.hitTimer >= rightAsia_ultimate.hitInterval) {
            rightAsia_ultimate.hitTimer = 0.0f;
            
            // Check if target is in range
            if (asia_is_in_ultimate_range(rightFighter->x, leftFighter->x, rightAsia_ultimate.range)) {
                // Deal damage
                leftFighter_subtract_health(rightAsia_ultimate.damagePerHit);
                rightFighter_add_ultimate(rightAsia_ultimate.damagePerHit / 3);
            }
            
            rightAsia_ultimate.hitCount++;
            
            // Check if we've done all hits
            if (rightAsia_ultimate.hitCount >= rightAsia_ultimate.totalHits) {
                rightAsia_ultimate.active = 0;
            }
        }
        
        // Deactivate if no longer in ultimate state
        if (rightFighter_currentState != STATE_ULTIMATE) {
            rightAsia_ultimate.active = 0;
        }
    }
}