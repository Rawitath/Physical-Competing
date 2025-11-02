#include "fightcontroller.h"
#include "../entity.h"
#include <SDL3/SDL.h>
#include "leftFighter.h"
#include "rightFighter.h"
#include "characterstate.h"
#include "roundsystem.h"
#include "allfighterstruct.h"
#include "timecounter.h"
#include "selectionmenu/shadescreen.h"
#include "../timesystem.h"
#include <math.h>
#include "fighterstruct.h"
#include "../scenecontroller.h"
#include <stdio.h>


// External variables from fighters
extern Entity* leftFighter;
extern Entity* rightFighter;
extern CharacterState leftFighter_currentState;
extern CharacterState rightFighter_currentState;
extern int leftFighter_facingRight;
extern int rightFighter_facingRight;
extern float leftFighter_stateTimer;
extern float rightFighter_stateTimer;
extern int leftFighter_health;
extern int rightFighter_health;

// Forward declarations for entity functions
void fightcontroller_start();
void fightcontroller_poll(SDL_Event* event);
void fightcontroller_loop();
void fightcontroller_render(SDL_Renderer* renderer);
void fightcontroller_destroy();

// Attack detection functions
void check_leftfighter_attack();
void check_rightfighter_attack();
int is_in_attack_range(float attacker_x, float target_x, float attacker_facing, float attack_range);
int is_facing_target(float attacker_x, float target_x, int attacker_facing);
int get_attack_damage(CharacterState attack_state, int fighter_index);
float get_attack_range(CharacterState attack_state, int fighter_index);
void freeze_fighters();
void unfreeze_fighters();

typedef enum {
    FIGHT_STATE_STARTING,
    FIGHT_STATE_FIGHTING,
    FIGHT_STATE_ROUND_OVER,
    FIGHT_STATE_FADEOUT
} FightState;
static FightState currentFightState;
static float fightStateTimer;

// Timers and constants for Fluke's horse collision damage
static float left_horse_damage_timer = 0.0f;
static float right_horse_damage_timer = 0.0f;
const float HORSE_DAMAGE_COOLDOWN = 0.5f; // Time between damage ticks
const int HORSE_COLLISION_DAMAGE = 5;     // Damage per tick


// Global entity pointer
Entity* fightcontroller;

// Track previous states to detect attack start
CharacterState leftfighter_prev_state = STATE_IDLE;
CharacterState rightfighter_prev_state = STATE_IDLE;

int fightcontroller_initial_countdown = 4;
int fightcontroller_round_time = 120;
int fightcontroller_exit_times = 5;

void fightcontroller_init() {
    fightcontroller = create_entity(
        NULL,
        &fightcontroller_start,
        &fightcontroller_poll,
        &fightcontroller_loop,
        &fightcontroller_render,
        &fightcontroller_destroy
    );
}

void fightcontroller_start() {
    // Initialization logic on scene start
    leftfighter_prev_state = STATE_IDLE;
    rightfighter_prev_state = STATE_IDLE;
    currentFightState = FIGHT_STATE_STARTING;
    fightStateTimer = 0.0f;
    counter_set_time(fightcontroller_initial_countdown); // Initial countdown
    shadescreen_set_instant(1);
}

void fightcontroller_poll(SDL_Event* event) {
    // Debug controls (optional - remove in production)
    // if(event->type == SDL_EVENT_KEY_DOWN){
    //     if(event->key.scancode == SDL_SCANCODE_1){
    //         leftFighter_subtract_health(1);
    //     }
    //     if(event->key.scancode == SDL_SCANCODE_2){
    //         leftFighter_add_health(1);
    //     }
    //     if(event->key.scancode == SDL_SCANCODE_3){
    //         leftFighter_subtract_ultimate(1);
    //     }
    //     if(event->key.scancode == SDL_SCANCODE_4){
    //         leftFighter_add_ultimate(1);
    //     }
    //     if(event->key.scancode == SDL_SCANCODE_5){
    //         leftFighter_subtract_break(1);
    //     }
    //     if(event->key.scancode == SDL_SCANCODE_6){
    //         leftFighter_add_break(1);
    //     }
    // }
}

void fightcontroller_loop() {
    float delta = get_delta();
    fightStateTimer += delta;

    switch (currentFightState) {
        case FIGHT_STATE_STARTING:
            freeze_fighters();
            shadescreen_set(0);
            // Countdown from 4 to 1, then "FIGHT"
            if (fightStateTimer >= fightcontroller_initial_countdown) {
                fightStateTimer = 0.0f;
                counter_set_time(currentTime - 1);
                if (currentTime <= 0) {
                    // "FIGHT" would be displayed here, then we switch state
                    // For now, let's just switch
                    currentFightState = FIGHT_STATE_FIGHTING;
                    unfreeze_fighters();
                    counter_set_max_time(fightcontroller_round_time); // Set round timer
                    counter_set_time(fightcontroller_round_time);
                }
            }
            break;

        case FIGHT_STATE_FIGHTING:
            // Normal fight logic
            check_leftfighter_attack();
            check_rightfighter_attack();

            // Check for round end
            if (currentTime <= 0 || leftFighter_health <= 0 || rightFighter_health <= 0) {
                currentFightState = FIGHT_STATE_ROUND_OVER;
                fightStateTimer = 0.0f;
                freeze_fighters();
            }
            break;
        case FIGHT_STATE_ROUND_OVER:
            freeze_fighters();
            // Wait for 5 seconds
            if (fightStateTimer >= fightcontroller_exit_times) {
                currentFightState = FIGHT_STATE_FADEOUT;
                shadescreen_set(1); // Start fade to black
            }
            break;

        case FIGHT_STATE_FADEOUT:
            sc_load_scene(0); //this scene
            // Screen is fading. Nothing to do here for now.
            // We could transition to another scene after the fade.
            break;
    }

    // Horse collision damage logic, should run only when fighting
    if (currentFightState == FIGHT_STATE_FIGHTING) {
        left_horse_damage_timer += delta;
        right_horse_damage_timer += delta;

        // Check for collision between fighters
        int colliding = fabsf(leftFighter->x - rightFighter->x) < (leftFighter->w + rightFighter->w) / 2 &&
                        fabsf(leftFighter->y - rightFighter->y) < (leftFighter->h + rightFighter->h) / 2;

        if (colliding) {
            if (leftFighter_currentState == STATE_FLUKE_HORSE_WALK && left_horse_damage_timer >= HORSE_DAMAGE_COOLDOWN) {
                rightFighter_subtract_health(HORSE_COLLISION_DAMAGE);
                left_horse_damage_timer = 0.0f;
            }
            if (rightFighter_currentState == STATE_FLUKE_HORSE_WALK && right_horse_damage_timer >= HORSE_DAMAGE_COOLDOWN) {
                leftFighter_subtract_health(HORSE_COLLISION_DAMAGE);
                right_horse_damage_timer = 0.0f;
            }
        }
    }
}


void freeze_fighters() {
    leftFighter_set_frozen(1);
    rightFighter_set_frozen(1);
}

void unfreeze_fighters() {
    leftFighter_set_frozen(0);
    rightFighter_set_frozen(0);
}

void check_leftfighter_attack() {
    extern CharacterState leftFighter_currentState;
    extern int leftFighter_facingRight;
    extern float leftFighter_stateTimer;
    
    // Check if just entered an attack state (state changed to attack)
    int is_new_attack = (leftfighter_prev_state != leftFighter_currentState) && 
                        (leftFighter_stateTimer < 0.05f); // Within first few frames
    
    if (!is_new_attack) {
        leftfighter_prev_state = leftFighter_currentState;
        return;
    }
    
    // Determine attack type
    int is_attack_state = 0;
    int is_crouching_attack = 0;
    int is_skill_or_ultimate = 0;
    
    switch(leftFighter_currentState) {
        case STATE_LIGHT_PUNCH:
        case STATE_HEAVY_PUNCH:
            is_attack_state = 1;
            break;
        case STATE_LOW_LIGHT_PUNCH:
        case STATE_LOW_HEAVY_PUNCH:
            is_attack_state = 1;
            is_crouching_attack = 1;
            break;
        case STATE_SKILL1:
        case STATE_SKILL2:
        case STATE_SKILL3:
        case STATE_ULTIMATE:
            is_attack_state = 1;
            is_skill_or_ultimate = 1;
            break;
        default:
            leftfighter_prev_state = leftFighter_currentState;
            return; // Not an attack state
    }
    
    if (!is_attack_state) {
        leftfighter_prev_state = leftFighter_currentState;
        return;
    }
    
    // Get attack range from fighter stats
    float attack_range = get_attack_range(leftFighter_currentState, rs_leftfighter);
    
    // Check if target is in range and facing correct direction
    extern CharacterState rightFighter_currentState;
    
    if (is_in_attack_range(leftFighter->x, rightFighter->x, leftFighter_facingRight, attack_range) &&
        is_facing_target(leftFighter->x, rightFighter->x, leftFighter_facingRight)) {
        
        // Skills and Ultimate bypass blocks
        int is_blocked = 0;
        if (!is_skill_or_ultimate) {
            if (rightFighter_currentState == STATE_BLOCK_STAND && !is_crouching_attack) {
                is_blocked = 1;
            } else if (rightFighter_currentState == STATE_BLOCK_CROUCH && is_crouching_attack) {
                is_blocked = 1;
            }
        }
        
        // Check if attack type matches target stance (only for normal attacks)
        int hit_connects = 1;
        if (!is_crouching_attack && !is_skill_or_ultimate && rightFighter_currentState == STATE_CROUCH) {
            hit_connects = 0; // Standing attack misses crouching target
        }
        
        if (hit_connects && !is_blocked) {
            // Deal damage from fighter stats
            int damage = get_attack_damage(leftFighter_currentState, rs_leftfighter);
            rightFighter_subtract_health(damage);
            
            // Add ultimate gauge for attacker
            if (is_skill_or_ultimate) {
                leftFighter_add_ultimate(damage / 3);
            } else {
                leftFighter_add_ultimate(damage / 2);
            }
        } else if (is_blocked) {
            // Reduce break gauge on successful block
            int damage = get_attack_damage(leftFighter_currentState, rs_leftfighter);
            rightFighter_subtract_break(damage / 3);
            
            // Small ultimate gain for blocker
            rightFighter_add_ultimate(2);
        }
    }
    
    leftfighter_prev_state = leftFighter_currentState;
}

void check_rightfighter_attack() {
    extern CharacterState rightFighter_currentState;
    extern int rightFighter_facingRight;
    extern float rightFighter_stateTimer;
    
    // Check if just entered an attack state
    int is_new_attack = (rightfighter_prev_state != rightFighter_currentState) && 
                        (rightFighter_stateTimer < 0.05f);
    
    if (!is_new_attack) {
        rightfighter_prev_state = rightFighter_currentState;
        return;
    }
    
    // Determine attack type
    int is_attack_state = 0;
    int is_crouching_attack = 0;
    int is_skill_or_ultimate = 0;
    
    switch(rightFighter_currentState) {
        case STATE_LIGHT_PUNCH:
        case STATE_HEAVY_PUNCH:
            is_attack_state = 1;
            break;
        case STATE_LOW_LIGHT_PUNCH:
        case STATE_LOW_HEAVY_PUNCH:
            is_attack_state = 1;
            is_crouching_attack = 1;
            break;
        case STATE_SKILL1:
        case STATE_SKILL2:
        case STATE_SKILL3:
        case STATE_ULTIMATE:
            is_attack_state = 1;
            is_skill_or_ultimate = 1;
            break;
        default:
            rightfighter_prev_state = rightFighter_currentState;
            return;
    }
    
    if (!is_attack_state) {
        rightfighter_prev_state = rightFighter_currentState;
        return;
    }
    
    // Get attack range from fighter stats
    float attack_range = get_attack_range(rightFighter_currentState, rs_rightfighter);
    
    // Check if target is in range and facing correct direction
    extern CharacterState leftFighter_currentState;
    
    if (is_in_attack_range(rightFighter->x, leftFighter->x, rightFighter_facingRight, attack_range) &&
        is_facing_target(rightFighter->x, leftFighter->x, rightFighter_facingRight)) {
        
        // Skills and Ultimate bypass blocks
        int is_blocked = 0;
        if (!is_skill_or_ultimate) {
            if (leftFighter_currentState == STATE_BLOCK_STAND && !is_crouching_attack) {
                is_blocked = 1;
            } else if (leftFighter_currentState == STATE_BLOCK_CROUCH && is_crouching_attack) {
                is_blocked = 1;
            }
        }
        
        // Check if attack type matches target stance (only for normal attacks)
        int hit_connects = 1;
        if (!is_crouching_attack && !is_skill_or_ultimate && leftFighter_currentState == STATE_CROUCH) {
            hit_connects = 0;
        }
        
        if (hit_connects && !is_blocked) {
            // Deal damage from fighter stats
            int damage = get_attack_damage(rightFighter_currentState, rs_rightfighter);
            leftFighter_subtract_health(damage);
            
            // Add ultimate gauge for attacker
            if (is_skill_or_ultimate) {
                rightFighter_add_ultimate(damage / 3);
            } else {
                rightFighter_add_ultimate(damage / 2);
            }
        } else if (is_blocked) {
            // Reduce break gauge on successful block
            int damage = get_attack_damage(rightFighter_currentState, rs_rightfighter);
            leftFighter_subtract_break(damage / 3);
            
            // Small ultimate gain for blocker
            leftFighter_add_ultimate(2);
        }
    }
    
    rightfighter_prev_state = rightFighter_currentState;
}

int is_in_attack_range(float attacker_x, float target_x, float attacker_facing, float attack_range) {
    float distance = fabsf(target_x - attacker_x);
    return distance <= attack_range;
}

int is_facing_target(float attacker_x, float target_x, int attacker_facing) {
    // attacker_facing: 0 = left, 1 = right
    if (attacker_facing == 1) {
        return target_x >= attacker_x; // Facing right, target should be on right
    } else {
        return target_x <= attacker_x; // Facing left, target should be on left
    }
}

// Get damage from fighter stats based on attack state
int get_attack_damage(CharacterState attack_state, int fighter_index) {
    if (fighter_index < 0 || fighter_index >= 4) return 0;
    
    Fighter* fighter = allFighters[fighter_index];
    if (fighter == NULL) return 0;
    
    switch(attack_state) {
        case STATE_LIGHT_PUNCH:
            return fighter->lightDamage;
        case STATE_HEAVY_PUNCH:
            return fighter->heavyDamage;
        case STATE_LOW_LIGHT_PUNCH:
            return fighter->crouchLightDamage;
        case STATE_LOW_HEAVY_PUNCH:
            return fighter->crouchHeavyDamage;
        case STATE_SKILL1:
            return fighter->skill1Damage;
        case STATE_SKILL2:
            return fighter->skill2Damage;
        case STATE_SKILL3:
            return fighter->skill3Damage;
        case STATE_ULTIMATE:
            return fighter->ultimateDamage;
        default:
            return 0;
    }
}

// Get attack range from fighter stats based on attack state
float get_attack_range(CharacterState attack_state, int fighter_index) {
    if (fighter_index < 0 || fighter_index >= 4) return 0.0f;
    
    Fighter* fighter = allFighters[fighter_index];
    if (fighter == NULL) return 0.0f;
    
    switch(attack_state) {
        case STATE_LIGHT_PUNCH:
            return fighter->lightRange;
        case STATE_HEAVY_PUNCH:
            return fighter->heavyRange;
        case STATE_LOW_LIGHT_PUNCH:
            return fighter->crouchLightRange;
        case STATE_LOW_HEAVY_PUNCH:
            return fighter->crouchHeavyRange;
        case STATE_SKILL1:
            return fighter->skill1Range;
        case STATE_SKILL2:
            return fighter->skill2Range;
        case STATE_SKILL3:
            return fighter->skill3Range;
        case STATE_ULTIMATE:
            return fighter->ultimateRange;
        default:
            return 0.0f;
    }
}

void fightcontroller_render(SDL_Renderer* renderer) {
    // This is a controller entity, so it doesn't render anything
}

void fightcontroller_destroy() {
    destroy_entity(fightcontroller);
}