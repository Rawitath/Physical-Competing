#include "fightcontroller.h"
#include "../entity.h"
#include <SDL3/SDL.h>
#include "leftFighter.h"
#include "rightFighter.h"
#include "characterstate.h"
#include <math.h>

// External variables from fighters
extern Entity* leftFighter;
extern Entity* rightFighter;
extern CharacterState leftFighter_currentState;
extern CharacterState rightFighter_currentState;
extern int leftFighter_facingRight;
extern int rightFighter_facingRight;
extern float leftFighter_stateTimer;
extern float rightFighter_stateTimer;

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
int get_attack_damage(CharacterState attack_state);

// Global entity pointer
Entity* fightcontroller;

// Attack range settings
#define LIGHT_ATTACK_RANGE 1.5f
#define HEAVY_ATTACK_RANGE 1.8f
#define CROUCH_LIGHT_ATTACK_RANGE 1.3f
#define CROUCH_HEAVY_ATTACK_RANGE 1.5f
#define SKILL_ATTACK_RANGE 2.5f
#define ULTIMATE_ATTACK_RANGE 3.0f

// Damage values
#define LIGHT_DAMAGE 5
#define HEAVY_DAMAGE 10
#define CROUCH_LIGHT_DAMAGE 4
#define CROUCH_HEAVY_DAMAGE 8
#define SKILL1_DAMAGE 15
#define SKILL2_DAMAGE 18
#define SKILL3_DAMAGE 20
#define ULTIMATE_DAMAGE 35

// Track previous states to detect attack start
CharacterState leftfighter_prev_state = STATE_IDLE;
CharacterState rightfighter_prev_state = STATE_IDLE;

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
}

void fightcontroller_poll(SDL_Event* event) {
    // Debug controls (optional - remove in production)
    if(event->type == SDL_EVENT_KEY_DOWN){
        if(event->key.scancode == SDL_SCANCODE_1){
            leftFighter_subtract_health(1);
        }
        if(event->key.scancode == SDL_SCANCODE_2){
            leftFighter_add_health(1);
        }
        if(event->key.scancode == SDL_SCANCODE_3){
            leftFighter_subtract_ultimate(1);
        }
        if(event->key.scancode == SDL_SCANCODE_4){
            leftFighter_add_ultimate(1);
        }
        if(event->key.scancode == SDL_SCANCODE_5){
            leftFighter_subtract_break(1);
        }
        if(event->key.scancode == SDL_SCANCODE_6){
            leftFighter_add_break(1);
        }
    }
}

void fightcontroller_loop() {
    // Check for attacks every frame
    check_leftfighter_attack();
    check_rightfighter_attack();
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
    
    // Determine attack type and range
    float attack_range = 0.0f;
    int is_crouching_attack = 0;
    int is_skill_or_ultimate = 0;
    
    switch(leftFighter_currentState) {
        case STATE_LIGHT_PUNCH:
            attack_range = LIGHT_ATTACK_RANGE;
            break;
        case STATE_HEAVY_PUNCH:
            attack_range = HEAVY_ATTACK_RANGE;
            break;
        case STATE_LOW_LIGHT_PUNCH:
            attack_range = CROUCH_LIGHT_ATTACK_RANGE;
            is_crouching_attack = 1;
            break;
        case STATE_LOW_HEAVY_PUNCH:
            attack_range = CROUCH_HEAVY_ATTACK_RANGE;
            is_crouching_attack = 1;
            break;
        case STATE_SKILL1:
        case STATE_SKILL2:
        case STATE_SKILL3:
            attack_range = SKILL_ATTACK_RANGE;
            is_skill_or_ultimate = 1;
            break;
        case STATE_ULTIMATE:
            attack_range = ULTIMATE_ATTACK_RANGE;
            is_skill_or_ultimate = 1;
            break;
        default:
            leftfighter_prev_state = leftFighter_currentState;
            return; // Not an attack state
    }
    
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
            // Deal damage
            int damage = get_attack_damage(leftFighter_currentState);
            rightFighter_subtract_health(damage);
            
            // Add ultimate gauge for attacker (more for skills/ultimate)
            if (is_skill_or_ultimate) {
                leftFighter_add_ultimate(damage / 3);
            } else {
                leftFighter_add_ultimate(damage / 2);
            }
        } else if (is_blocked) {
            // Reduce break gauge on successful block
            rightFighter_subtract_break(get_attack_damage(leftFighter_currentState) / 3);
            
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
    
    // Determine attack type and range
    float attack_range = 0.0f;
    int is_crouching_attack = 0;
    int is_skill_or_ultimate = 0;
    
    switch(rightFighter_currentState) {
        case STATE_LIGHT_PUNCH:
            attack_range = LIGHT_ATTACK_RANGE;
            break;
        case STATE_HEAVY_PUNCH:
            attack_range = HEAVY_ATTACK_RANGE;
            break;
        case STATE_LOW_LIGHT_PUNCH:
            attack_range = CROUCH_LIGHT_ATTACK_RANGE;
            is_crouching_attack = 1;
            break;
        case STATE_LOW_HEAVY_PUNCH:
            attack_range = CROUCH_HEAVY_ATTACK_RANGE;
            is_crouching_attack = 1;
            break;
        case STATE_SKILL1:
        case STATE_SKILL2:
        case STATE_SKILL3:
            attack_range = SKILL_ATTACK_RANGE;
            is_skill_or_ultimate = 1;
            break;
        case STATE_ULTIMATE:
            attack_range = ULTIMATE_ATTACK_RANGE;
            is_skill_or_ultimate = 1;
            break;
        default:
            rightfighter_prev_state = rightFighter_currentState;
            return;
    }
    
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
            // Deal damage
            int damage = get_attack_damage(rightFighter_currentState);
            leftFighter_subtract_health(damage);
            
            // Add ultimate gauge for attacker (more for skills/ultimate)
            if (is_skill_or_ultimate) {
                rightFighter_add_ultimate(damage / 3);
            } else {
                rightFighter_add_ultimate(damage / 2);
            }
            
            // Break guard on skills/ultimate hit
            if (is_skill_or_ultimate) {
                leftFighter_subtract_break(damage / 2);
            }
        } else if (is_blocked) {
            // Reduce break gauge on successful block
            leftFighter_subtract_break(get_attack_damage(rightFighter_currentState) / 3);
            
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

int get_attack_damage(CharacterState attack_state) {
    switch(attack_state) {
        case STATE_LIGHT_PUNCH:
            return LIGHT_DAMAGE;
        case STATE_HEAVY_PUNCH:
            return HEAVY_DAMAGE;
        case STATE_LOW_LIGHT_PUNCH:
            return CROUCH_LIGHT_DAMAGE;
        case STATE_LOW_HEAVY_PUNCH:
            return CROUCH_HEAVY_DAMAGE;
        case STATE_SKILL1:
            return SKILL1_DAMAGE;
        case STATE_SKILL2:
            return SKILL2_DAMAGE;
        case STATE_SKILL3:
            return SKILL3_DAMAGE;
        case STATE_ULTIMATE:
            return ULTIMATE_DAMAGE;
        default:
            return 0;
    }
}

void fightcontroller_render(SDL_Renderer* renderer) {
    // This is a controller entity, so it doesn't render anything
}

void fightcontroller_destroy() {
    destroy_entity(fightcontroller);
}