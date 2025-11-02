#include "bas.h"
#include <SDL3/SDL_scancode.h>
#include "../entity.h"
#include "jobpaper.h"
#include "../scene.h"
#include "basanim.h"
#include "playerinput.h"
#include "leftFighter.h"
#include "rightFighter.h"
#include "../timesystem.h"
#include "characterstate.h"
#include <stdio.h>
#include <math.h>

Fighter bas;

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

static UltimateState leftBas_ultimate = {0};
static UltimateState rightBas_ultimate = {0};

void bas_skill1(Entity* fighter, int direction);
void bas_skill2(Entity* fighter, int direction);
void bas_skill3(Entity* fighter, int direction);
void bas_ultimate(Entity* fighter);

void bas_init() {
    bas.id = 1;
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
    bas.skill1Damage = 15;
    bas.skill2Damage = 18;
    bas.skill3Damage = 20;
    bas.ultimateDamage = 35;    // Total damage (7 per hit × 5 hits)
    
    // Attack ranges (bas - Medium range)
    bas.lightRange = 1.5f;
    bas.heavyRange = 1.8f;
    bas.crouchLightRange = 1.3f;
    bas.crouchHeavyRange = 1.5f;
    bas.skill1Range = 2.5f;
    bas.skill2Range = 2.5f;
    bas.skill3Range = 2.5f;
    bas.ultimateRange = 3.0f;
    
    bas.fighterAnim = basAnim;

    bas.skill1 = &bas_skill1;
    bas.skill1Time = 4;
    bas.skill1Keys[0] = INPUT_JUMP;
    bas.skill1Keys[1] = INPUT_JUMP;
    bas.skill1Keys[2] = INPUT_LIGHT;
    bas.skill1Keys[3] = INPUT_HEAVY;

    bas.skill2 = &bas_skill2;
    bas.skill2Time = 5;
    bas.skill2Keys[0] = INPUT_LIGHT;
    bas.skill2Keys[1] = INPUT_LIGHT;
    bas.skill2Keys[2] = INPUT_LIGHT;
    bas.skill2Keys[3] = INPUT_JUMP;

    bas.skill3 = &bas_skill3;
    bas.skill3Time = 3.5;
    bas.skill3Keys[0] = INPUT_HEAVY;
    bas.skill3Keys[1] = INPUT_HEAVY;
    bas.skill3Keys[2] = INPUT_HEAVY;
    bas.skill3Keys[3] = INPUT_LIGHT;

    bas.ultimate = &bas_ultimate;
    bas.ultimateTime = 6;
}

void bas_skill1(Entity* fighter, int direction) {}

void bas_skill2(Entity* fighter, int direction) {
    if(!jobpaper) jobpaper_init();
    add_entity(fighter->scene, jobpaper);
    release_jobpaper(fighter, direction);
}

void bas_skill3(Entity* fighter, int direction) {
    
}

// Check if target is in range
int is_in_ultimate_range(float attacker_x, float target_x, float range) {
    return fabsf(target_x - attacker_x) <= range;
}

void bas_ultimate(Entity* fighter) {
    // Determine which fighter this is (left or right)
    extern Entity* leftFighter;
    extern Entity* rightFighter;
    
    UltimateState* state = NULL;
    
    if (fighter == leftFighter) {
        state = &leftBas_ultimate;
    } else if (fighter == rightFighter) {
        state = &rightBas_ultimate;
    }
    
    if (state) {
        // Initialize ultimate state
        state->active = 1;
        state->hitCount = 0;
        state->hitTimer = 0.0f;
        state->hitInterval = 0.6f;  // 0.6 seconds between each hit
        state->totalHits = 5;        // 5 hits total
        state->damagePerHit = 7;     // 7 damage per hit (35 total)
        state->range = bas.ultimateRange;
    }
}

// This function should be called in the main game loop
void bas_ultimate_update() {
    extern Entity* leftFighter;
    extern Entity* rightFighter;
    extern CharacterState leftFighter_currentState;
    extern CharacterState rightFighter_currentState;
    
    float delta = get_delta();
    
    // Update left fighter's ultimate
    if (leftBas_ultimate.active) {
        leftBas_ultimate.hitTimer += delta;
        
        // Check if it's time for the next hit
        if (leftBas_ultimate.hitTimer >= leftBas_ultimate.hitInterval) {
            leftBas_ultimate.hitTimer = 0.0f;
            
            // Check if target is in range
            if (is_in_ultimate_range(leftFighter->x, rightFighter->x, leftBas_ultimate.range)) {
                // Deal damage
                rightFighter_subtract_health(leftBas_ultimate.damagePerHit);
                leftFighter_add_ultimate(leftBas_ultimate.damagePerHit / 3);
            }
            
            leftBas_ultimate.hitCount++;
            
            // Check if we've done all hits
            if (leftBas_ultimate.hitCount >= leftBas_ultimate.totalHits) {
                leftBas_ultimate.active = 0;
            }
        }
        
        // Deactivate if no longer in ultimate state
        if (leftFighter_currentState != STATE_ULTIMATE) {
            leftBas_ultimate.active = 0;
        }
    }
    
    // Update right fighter's ultimate
    if (rightBas_ultimate.active) {
        rightBas_ultimate.hitTimer += delta;
        
        // Check if it's time for the next hit
        if (rightBas_ultimate.hitTimer >= rightBas_ultimate.hitInterval) {
            rightBas_ultimate.hitTimer = 0.0f;
            
            // Check if target is in range
            if (is_in_ultimate_range(rightFighter->x, leftFighter->x, rightBas_ultimate.range)) {
                // Deal damage
                leftFighter_subtract_health(rightBas_ultimate.damagePerHit);
                rightFighter_add_ultimate(rightBas_ultimate.damagePerHit / 3);
            }
            
            rightBas_ultimate.hitCount++;
            
            // Check if we've done all hits
            if (rightBas_ultimate.hitCount >= rightBas_ultimate.totalHits) {
                rightBas_ultimate.active = 0;
            }
        }
        
        // Deactivate if no longer in ultimate state
        if (rightFighter_currentState != STATE_ULTIMATE) {
            rightBas_ultimate.active = 0;
        }
    }
}