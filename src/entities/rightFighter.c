#include "../entity.h"
#include "rightFighter.h"
#include "../timesystem.h"
#include "../scene.h"
#include "../scenecontroller.h"
#include <stdio.h>
#include "../animation.h"

#include <SDL3/SDL.h>

#include "fighteranim.h"
#include "golfanim.h"
#include "flukeanim.h"
#include "characterstate.h"
#include "playerkeybind.h"
#include "playerinput.h"
#include "roundsystem.h"
#include "allfighterstruct.h"
#include "fighterstruct.h"
#include "righthealthbar.h"
#include "rightultibar.h"

void rightFighter_start();
void rightFighter_poll(SDL_Event* event);
void rightFighter_loop();
void rightFighter_render(SDL_Renderer* renderer);
void rightFighter_destroy();

float rightFighter_x = 0;
float rightFighter_groundLevel = -3.5;

void rightFighter_init(){
    rightFighter = create_entity(
            NULL,
            &rightFighter_start,
            &rightFighter_poll,
            &rightFighter_loop,
            &rightFighter_render,
            &rightFighter_destroy
        );
    rightFighter->w *= 0.55;
    rightFighter->h *= 0.55;
    // rightFighter_anim will be set in rightFighter_start
}

// Animation pointers
FighterAnim* rightFighter_anim = NULL;

CharacterState rightFighter_currentState = STATE_IDLE;
// Animation state variables
int rightFighter_currentAnimIndex = idle;
int rightFighter_facingRight = 0; // 0 = left, 1 = right
float rightFighter_velocityY = 0;
float rightFighter_gravity = 80.0;
float rightFighter_jumpForce = 30.0;
int rightFighter_isGrounded = 1;
float rightFighter_moveSpeed = 9.0;
PlayerKeybind rightFighter_keybind;
float rightFighter_currentFrameCounter = 0;

//Stats
int rightFighter_health = 100;
int rightFighter_ultimateGauge = 0;
int rightFighter_breakGauge = 100;
int rightFighter_isFrozen = 0;

// State timer
float rightFighter_stateTimer = 0.0;
float rightFighter_light_attack_timeout = 0.3;
float rightFighter_heavy_attack_timeout = 0.6;
float rightFighter_crouch_light_attack_timeout = 0.4;
float rightFighter_crouch_heavy_attack_timeout = 0.7;
float rightFighter_fall_timeout = 5;
float rightFighter_skill1_time = 6;
float rightFighter_skill2_time = 6;
float rightFighter_skill3_time = 6;
float rightFighter_ultimate_time = 4;
float rightFighter_damaged_timeout = 2;
float rightFighter_fluke_horse_timeout = 7;


// Animation segment points
int rightFighter_block_stand_hold_frame = 0;
int rightFighter_block_crouch_hold_frame = 0;

// Combo system
#define MAX_COMBO_LENGTH 4
#define COMBO_TIMEOUT 1.0f

PlayerInput rightFighter_comboBuffer[MAX_COMBO_LENGTH];
int rightFighter_comboCount = 0;
float rightFighter_comboTimer = 0.0f;

void rightFighter_reset_combo() {
    rightFighter_comboCount = 0;
    rightFighter_comboTimer = 0.0f;
    for(int i = 0; i < MAX_COMBO_LENGTH; i++) {
        rightFighter_comboBuffer[i] = INPUT_NONE;
    }
}

void rightFighter_add_to_combo(PlayerInput input) {
    if(rightFighter_comboCount < MAX_COMBO_LENGTH) {
        rightFighter_comboBuffer[rightFighter_comboCount] = input;
        rightFighter_comboCount++;
        rightFighter_comboTimer = 0.0f; // Reset timer when new input added
    }
}

int rightFighter_check_combo_pattern(PlayerInput p1, PlayerInput p2, PlayerInput p3, PlayerInput p4) {
    if(rightFighter_comboCount != 4) return 0;
    return (rightFighter_comboBuffer[0] == p1 && 
            rightFighter_comboBuffer[1] == p2 && 
            rightFighter_comboBuffer[2] == p3 && 
            rightFighter_comboBuffer[3] == p4);
}

int rightFighter_check_and_execute_skill() {
    // TODO: Implement actual skill combos for rightFighter
    // Example: Skill 3: Light, Heavy, Light, Heavy
    if(rightFighter_check_combo_pattern(allFighters[rs_rightfighter]->skill1Keys[0],
                           allFighters[rs_rightfighter]->skill1Keys[1],
                           allFighters[rs_rightfighter]->skill1Keys[2],
                           allFighters[rs_rightfighter]->skill1Keys[3])) {
        rightFighter_currentState = STATE_SKILL1;
        allFighters[rs_rightfighter]->skill1(rightFighter, rightFighter_facingRight);
        rightFighter_stateTimer = 0.0f;
        rightFighter_reset_combo();
        return 1;
    }
    if(rightFighter_check_combo_pattern(allFighters[rs_rightfighter]->skill2Keys[0],
                           allFighters[rs_rightfighter]->skill2Keys[1],
                           allFighters[rs_rightfighter]->skill2Keys[2],
                           allFighters[rs_rightfighter]->skill2Keys[3])) {
        rightFighter_currentState = STATE_SKILL2;
        allFighters[rs_rightfighter]->skill2(rightFighter, rightFighter_facingRight);
        rightFighter_stateTimer = 0.0f;
        rightFighter_reset_combo();
        return 1;
    }
    if(rightFighter_check_combo_pattern(allFighters[rs_rightfighter]->skill3Keys[0],
                           allFighters[rs_rightfighter]->skill3Keys[1],
                           allFighters[rs_rightfighter]->skill3Keys[2],
                           allFighters[rs_rightfighter]->skill3Keys[3])) {
        rightFighter_currentState = STATE_SKILL3;
        allFighters[rs_rightfighter]->skill3(rightFighter, rightFighter_facingRight);
        rightFighter_stateTimer = 0.0f;
        rightFighter_reset_combo();
        return 1;
    }
    return 0;
}

void rightFighter_set_current_animation_state(int newAnimIndex) {
    if (rightFighter_currentAnimIndex != newAnimIndex) {
        rightFighter_currentAnimIndex = newAnimIndex;
        reset_animation_frame(rightFighter_anim, newAnimIndex + rightFighter_facingRight);
        rightFighter_currentFrameCounter = 0; // Reset frame counter when animation changes
    }
}

int rightFighter_get_anim_index_from_state(CharacterState state) {
    switch (state) {
        case STATE_WALK: return walk;
        case STATE_JUMP: return jump;
        case STATE_CROUCH: return crouching;
        case STATE_BLOCK_STAND: return block_stand;
        case STATE_BLOCK_RELEASE: return block_stand;
        case STATE_BLOCK_CROUCH: return block_crouch;
        case STATE_LIGHT_PUNCH: return light1; // Assuming light1 for generic light punch
        case STATE_HEAVY_PUNCH: return heavy1; // Assuming heavy1 for generic heavy punch
        case STATE_LOW_LIGHT_PUNCH: return crouch_light1; // Assuming crouch_light1 for low punch
        case STATE_LOW_HEAVY_PUNCH: return crouch_heavy1;
        case STATE_SKILL1: return skill1;
        case STATE_SKILL2: return skill2;
        case STATE_SKILL3: return skill3;
        case STATE_ULTIMATE: return ultimate;
        case STATE_FALL: return fall;
        case STATE_DAMAGED: return damaged;
        case STATE_FLUKE_HORSE: return fluke_horse;
        case STATE_FLUKE_HORSE_WALK: return fluke_horse_walk;
        default: return idle; // Fallback to idle
    }
}
void rightFighter_setup_player(){
    rightFighter_anim = allFighters[rs_rightfighter]->fighterAnim;
    rightFighter_currentAnimIndex = idle;
    rightFighter_gravity = 80.0f;
    rightFighter_jumpForce = 30.0f;
    rightFighter_moveSpeed = allFighters[rs_rightfighter]->speed;
    rightFighter_light_attack_timeout = allFighters[rs_rightfighter]->lightAttackTime;
    rightFighter_heavy_attack_timeout = allFighters[rs_rightfighter]->heavyAttackTime;
    rightFighter_crouch_light_attack_timeout = allFighters[rs_rightfighter]->crouchLightAttackTime;
    rightFighter_crouch_heavy_attack_timeout = allFighters[rs_rightfighter]->crouchHeavyAttackTime;
    rightFighter_skill1_time = allFighters[rs_rightfighter]->skill1Time;
    rightFighter_skill2_time = allFighters[rs_rightfighter]->skill2Time;
    rightFighter_skill3_time = allFighters[rs_rightfighter]->skill3Time;
    rightFighter_ultimate_time = allFighters[rs_rightfighter]->ultimateTime;
}

void rightFighter_start(){
    rightFighter_health = 100;
    rightFighter_ultimateGauge = 0;
    rightFighter_breakGauge = 100;
    rightFighter->x = 5;
    rightFighter_reset_combo();
    // Initialize keybinds (example default for Player 2)
    rightFighter_keybind._left = SDL_SCANCODE_LEFT;
    rightFighter_keybind._right = SDL_SCANCODE_RIGHT;
    rightFighter_keybind._jump = SDL_SCANCODE_UP;
    rightFighter_keybind._crouch = SDL_SCANCODE_DOWN;
    rightFighter_keybind._light_punch = SDL_SCANCODE_KP_1;
    rightFighter_keybind._heavy_punch = SDL_SCANCODE_KP_2;
    rightFighter_keybind._ultimate = SDL_SCANCODE_KP_3;
    rightFighter_keybind._block = SDL_SCANCODE_KP_0;

    // Assign a FighterAnim (e.g., Fluke's animations)
    // In a real game, this would be determined by player selection
    rightFighter_setup_player();
    rightFighter_currentState = STATE_IDLE;
    rightFighter->y = rightFighter_groundLevel;
    if (rightFighter_anim && rightFighter_anim->anims[block_stand]) {
        rightFighter_block_stand_hold_frame = rightFighter_anim->anims[block_stand]->imageCount / 2;
        rightFighter_block_crouch_hold_frame = rightFighter_anim->anims[block_crouch]->imageCount / 2;
    }

    // rightFighter_set_current_animation_state(idle);
}

void rightFighter_set_frozen(int frozen) {
    rightFighter_isFrozen = frozen;
}

void rightFighter_poll(SDL_Event* event){
    if(event->type == SDL_EVENT_KEY_DOWN){
        // กระโดด (W หรือ ลูกศรขึ้น)
        if((event->key.scancode == rightFighter_keybind._jump) && rightFighter_isGrounded){
            if(rightFighter_currentState != STATE_SKILL1 &&
               rightFighter_currentState != STATE_SKILL2 &&
               rightFighter_currentState != STATE_SKILL3 &&
               rightFighter_currentState != STATE_ULTIMATE &&
               rightFighter_currentState != STATE_CROUCH &&
               rightFighter_currentState != STATE_FALL &&
                !rightFighter_isFrozen && rightFighter_currentState != STATE_FLUKE_HORSE && rightFighter_currentState != STATE_FLUKE_HORSE_WALK){
            rightFighter_add_to_combo(INPUT_JUMP);
            if(!rightFighter_check_and_execute_skill()){
                rightFighter_currentState = STATE_JUMP;
                rightFighter_velocityY = rightFighter_jumpForce;
                rightFighter_isGrounded = 0;
            }
        }
        }
        if(event->key.scancode == rightFighter_keybind._block){
            if(rightFighter_currentState != STATE_LIGHT_PUNCH && 
               rightFighter_currentState != STATE_HEAVY_PUNCH &&
               rightFighter_currentState != STATE_BLOCK_RELEASE &&
               rightFighter_currentState != STATE_LOW_LIGHT_PUNCH &&
               rightFighter_currentState != STATE_LOW_HEAVY_PUNCH &&
               rightFighter_currentState != STATE_SKILL1 &&
               rightFighter_currentState != STATE_SKILL2 &&
               rightFighter_currentState != STATE_SKILL3 &&
               rightFighter_currentState != STATE_ULTIMATE &&
               rightFighter_currentState != STATE_FALL){
            rightFighter_add_to_combo(INPUT_BLOCK);
            rightFighter_check_and_execute_skill();
               }
        }
        
        // ต่อยเบา (J หรือ 2) - ยืนเท่านั้น
        if(event->key.scancode == rightFighter_keybind._light_punch){
            if(rightFighter_currentState != STATE_LIGHT_PUNCH && 
               rightFighter_currentState != STATE_HEAVY_PUNCH &&
               rightFighter_currentState != STATE_BLOCK_RELEASE &&
               rightFighter_currentState != STATE_LOW_LIGHT_PUNCH &&
               rightFighter_currentState != STATE_LOW_HEAVY_PUNCH &&
               rightFighter_currentState != STATE_SKILL1 &&
               rightFighter_currentState != STATE_SKILL2 &&
               rightFighter_currentState != STATE_SKILL3 &&
               rightFighter_currentState != STATE_ULTIMATE &&
               rightFighter_currentState != STATE_CROUCH &&
               rightFighter_currentState != STATE_FALL &&
               rightFighter_currentState != STATE_BLOCK_CROUCH){
                
                // Add to combo
                rightFighter_add_to_combo(INPUT_LIGHT);
                
                // Check if we can execute a skill
                if(!rightFighter_check_and_execute_skill()) {
                    // Normal light punch
                    rightFighter_currentState = STATE_LIGHT_PUNCH;
                }                
            }
        }
        
        // ต่อยหนัก (K หรือ 3) - ยืนเท่านั้น
        if(event->key.scancode == rightFighter_keybind._heavy_punch){
            if(rightFighter_currentState != STATE_LIGHT_PUNCH && 
               rightFighter_currentState != STATE_HEAVY_PUNCH &&
               rightFighter_currentState != STATE_BLOCK_RELEASE &&
               rightFighter_currentState != STATE_LOW_LIGHT_PUNCH &&
               rightFighter_currentState != STATE_LOW_HEAVY_PUNCH &&
               rightFighter_currentState != STATE_SKILL1 &&
               rightFighter_currentState != STATE_SKILL2 &&
               rightFighter_currentState != STATE_SKILL3 &&
               rightFighter_currentState != STATE_ULTIMATE &&
               rightFighter_currentState != STATE_CROUCH &&
               rightFighter_currentState != STATE_FALL &&
               rightFighter_currentState != STATE_BLOCK_CROUCH){
                
                // Add to combo
                rightFighter_add_to_combo(INPUT_HEAVY);
                
                // Check if we can execute a skill
                if(!rightFighter_check_and_execute_skill()) {
                    // Normal heavy punch
                    rightFighter_currentState = STATE_HEAVY_PUNCH;
                }                
            }
        }
        
        // Ultimate (I หรือ 5) - ไม่สามารถบล็อกได้
        if(rightFighter_ultimateGauge >= 100 && event->key.scancode == rightFighter_keybind._ultimate){
            if(rightFighter_currentState != STATE_LIGHT_PUNCH && 
               rightFighter_currentState != STATE_HEAVY_PUNCH &&
               rightFighter_currentState != STATE_BLOCK_RELEASE &&
               rightFighter_currentState != STATE_LOW_LIGHT_PUNCH &&
               rightFighter_currentState != STATE_LOW_HEAVY_PUNCH &&
               rightFighter_currentState != STATE_SKILL1 &&
               rightFighter_currentState != STATE_SKILL2 &&
               rightFighter_currentState != STATE_SKILL3 &&
               rightFighter_currentState != STATE_ULTIMATE &&
               rightFighter_currentState != STATE_CROUCH &&
               rightFighter_currentState != STATE_BLOCK_CROUCH &&
               rightFighter_currentState != STATE_FALL &&
               rightFighter_currentState != STATE_BLOCK_STAND){
                
                rightFighter_currentState = STATE_ULTIMATE;
                rightFighter_ultimateGauge = 0;
                rightFighter_stateTimer = 0.0f;
                allFighters[rs_rightfighter]->ultimate(rightFighter);
            }
        
                // printf("ULTIMATE ACTIVATED!\n");
            }
        
    }
    else if (event->type == SDL_EVENT_KEY_UP) {
        if (event->key.scancode == rightFighter_keybind._block) {
            if (rightFighter_currentState == STATE_BLOCK_STAND || rightFighter_currentState == STATE_BLOCK_CROUCH) {
                rightFighter_currentState = STATE_BLOCK_RELEASE;
            }
        }
    }
}

void rightFighter_on_block_release_complete() {
        rightFighter_currentState = STATE_IDLE;
    }

void rightFighter_on_fall_anim_complete() {
    // This function can be used if you want something to happen when the fall animation finishes
    // For now, we'll just freeze the animation, so this can be empty.
}

void rightFighter_loop(){
    float delta = get_delta();
    righthealthbar_set_health(rightFighter_health);
    rightultibar_set_health(rightFighter_ultimateGauge);
    // printf("%d, %d, %d, %d\n", rightFighter_comboBuffer[0], rightFighter_comboBuffer[1], rightFighter_comboBuffer[2], rightFighter_comboBuffer[3]);

    if (rightFighter_isFrozen) {
        if(rightFighter_health <= 0){
            rightFighter_currentState = STATE_FALL;
            goto animation_update;
        }
        rightFighter_currentState = STATE_IDLE;
        goto animation_update;
    }
    
    if (rightFighter_health <= 0) goto animation_update;
    //Fall logic
    if(rightFighter_currentState != STATE_FALL && rightFighter_breakGauge < 1){
        rightFighter_currentState = STATE_FALL;
        rightFighter_stateTimer = 0.0f; // Reset timer when entering fall state
    } else if (rightFighter_currentState == STATE_FALL) {
        // The rest of the loop is skipped while in STATE_FALL
    }


    // Update combo timer
    if(rightFighter_comboCount > 0) {
        rightFighter_comboTimer += delta;
        if(rightFighter_comboTimer >= COMBO_TIMEOUT) {
            // printf("Combo timeout! Resetting...\n");
            rightFighter_reset_combo();
        }
    }

    // Handle state timer for attacks
    if (rightFighter_currentState == STATE_LIGHT_PUNCH) {
        rightFighter_stateTimer += delta;
        if (rightFighter_stateTimer >= rightFighter_light_attack_timeout) {
            rightFighter_currentState = STATE_IDLE;
            rightFighter_stateTimer = 0.0f;
        }
    } else if (rightFighter_currentState == STATE_HEAVY_PUNCH) {
        rightFighter_stateTimer += delta;
        if (rightFighter_stateTimer >= rightFighter_heavy_attack_timeout) {
            rightFighter_currentState = STATE_IDLE;
            rightFighter_stateTimer = 0.0f;
        }
    } else if (rightFighter_currentState == STATE_LOW_LIGHT_PUNCH) {
        rightFighter_stateTimer += delta;
        if (rightFighter_stateTimer >= rightFighter_crouch_light_attack_timeout){
            rightFighter_currentState = STATE_CROUCH; // Return to crouch after low punch
            rightFighter_stateTimer = 0.0f;
        }
    } else if (rightFighter_currentState == STATE_LOW_HEAVY_PUNCH) {
        rightFighter_stateTimer += delta;
        if (rightFighter_stateTimer >= rightFighter_crouch_heavy_attack_timeout) {
            rightFighter_currentState = STATE_CROUCH; // Return to crouch after low heavy punch
            rightFighter_stateTimer = 0.0f;
        }
    } else if (rightFighter_currentState == STATE_FALL) {
        rightFighter_stateTimer += delta;
        if (rightFighter_stateTimer >= rightFighter_fall_timeout) {
            rightFighter_currentState = STATE_IDLE;
            rightFighter_breakGauge = 100;
            rightFighter_stateTimer = 0.0f;
        }
    } else if (rightFighter_currentState == STATE_DAMAGED){
        rightFighter_stateTimer += delta;
        if(rightFighter_stateTimer >= rightFighter_damaged_timeout){
            rightFighter_currentState = STATE_IDLE;
            rightFighter_stateTimer = 0.0f;
        }
    }
    else if (rightFighter_currentState == STATE_SKILL1) {
        rightFighter_stateTimer += delta;
        if (rightFighter_stateTimer >= rightFighter_skill1_time) {
            rightFighter_currentState = STATE_IDLE;
            rightFighter_stateTimer = 0.0f;
        }
    } else if (rightFighter_currentState == STATE_SKILL2) {
        rightFighter_stateTimer += delta;
        if (rightFighter_stateTimer >= rightFighter_skill2_time) {
            rightFighter_currentState = STATE_IDLE;
            rightFighter_stateTimer = 0.0f;
        }
    } else if (rightFighter_currentState == STATE_SKILL3) {
        rightFighter_stateTimer += delta;
        if (rightFighter_stateTimer >= rightFighter_skill3_time) {
            rightFighter_currentState = STATE_IDLE;
            rightFighter_stateTimer = 0.0f;
        }
    } else if (rightFighter_currentState == STATE_ULTIMATE) {
        rightFighter_stateTimer += delta;
        if (rightFighter_stateTimer >= rightFighter_ultimate_time) {
            if(rs_rightfighter != 0){ // 0 is fluke's ID
                rightFighter_currentState = STATE_IDLE;
                rightFighter_stateTimer = 0.0f;
            }
            else{
                rightFighter_currentState = STATE_FLUKE_HORSE;
                rightFighter_stateTimer = 0.0f;
            }
        }
    }
    else if (rightFighter_currentState == STATE_FLUKE_HORSE) {
        rightFighter_stateTimer += delta;
        if (rightFighter_stateTimer >= rightFighter_fluke_horse_timeout) {
            rightFighter_currentState = STATE_IDLE;
            rightFighter_stateTimer = 0.0f;
        }
    } else if (rightFighter_currentState == STATE_FLUKE_HORSE_WALK) {
        // This state is for animation, timeout is handled by STATE_FLUKE_HORSE
    }
     else {
        // Reset timer if not in an attack state
        rightFighter_stateTimer = 0.0f;
    }
    
    // อ่านค่า keyboard state
    const bool* keyState = SDL_GetKeyboardState(NULL);
    
    // ตรวจสอบการกดปุ่มบล็อก (L หรือ 1)
    int isBlocking = keyState[rightFighter_keybind._block];
    
    // ตรวจสอบการกดปุ่มนั่ง (S หรือ ลูกศรลง)
    int isCrouching = keyState[rightFighter_keybind._crouch];
    
    // ถ้าไม่ได้กำลังโจมตีหรือใช้สกิล ให้สามารถเคลื่อนไหวได้
    if(rightFighter_currentState != STATE_LIGHT_PUNCH && 
       rightFighter_currentState != STATE_HEAVY_PUNCH && 
       rightFighter_currentState != STATE_BLOCK_RELEASE &&
       rightFighter_currentState != STATE_LOW_LIGHT_PUNCH &&
       rightFighter_currentState != STATE_LOW_HEAVY_PUNCH &&
       rightFighter_currentState != STATE_SKILL1 &&
       rightFighter_currentState != STATE_SKILL2 &&
       rightFighter_currentState != STATE_SKILL3 &&
       rightFighter_currentState != STATE_FALL &&
       rightFighter_currentState != STATE_DAMAGED &&
       rightFighter_currentState != STATE_ULTIMATE){
        
        int moving = 0;
        
        // Determine character state based on input
        if(isBlocking && isCrouching && rightFighter_isGrounded) {
            rightFighter_currentState = STATE_BLOCK_CROUCH;
        }
        else if(isBlocking && rightFighter_isGrounded && rightFighter_currentState != STATE_JUMP){
            rightFighter_currentState = STATE_BLOCK_STAND;
        }
        // ถ้ากด Crouch เฉยๆ
        else if(isCrouching && rightFighter_isGrounded){
            rightFighter_currentState = STATE_CROUCH;
            
            // เช็คว่ากดปุ่มโจมตีในขณะนั่งหรือไม่
            if(keyState[rightFighter_keybind._light_punch]){
                rightFighter_currentState = STATE_LOW_LIGHT_PUNCH;
            }
            else if(keyState[rightFighter_keybind._heavy_punch]){
                rightFighter_currentState = STATE_LOW_HEAVY_PUNCH;
            }
        }
        // เดินซ้าย (A หรือ ลูกศรซ้าย)
        else if((keyState[rightFighter_keybind._left]) && !isCrouching){
            rightFighter->x -= rightFighter_moveSpeed * delta;
            rightFighter_facingRight = 0;
            if(rightFighter_isGrounded && rightFighter_currentState != STATE_CROUCH){
                if(rs_rightfighter == 0 && (rightFighter_currentState == STATE_FLUKE_HORSE || rightFighter_currentState == STATE_FLUKE_HORSE_WALK)){
                    rightFighter_currentState = STATE_FLUKE_HORSE_WALK;
                }
                else{
                    rightFighter_currentState = STATE_WALK;
                }
            }
            moving = 1;
        }
        // เดินขวา (D หรือ ลูกศรขวา)
        else if((keyState[rightFighter_keybind._right]) && !isCrouching){
            rightFighter->x += rightFighter_moveSpeed * delta;
            rightFighter_facingRight = 1;
            if(rightFighter_isGrounded && rightFighter_currentState != STATE_CROUCH){
                if(rs_rightfighter == 0 && (rightFighter_currentState == STATE_FLUKE_HORSE || rightFighter_currentState == STATE_FLUKE_HORSE_WALK)){
                    rightFighter_currentState = STATE_FLUKE_HORSE_WALK;
                }
                else{
                    rightFighter_currentState = STATE_WALK;
                }
            }
            moving = 1;
        }
        // ถ้าไม่กดปุ่มใดๆ และอยู่บนพื้น ให้ idle
        else if(!moving && rightFighter_isGrounded && rightFighter_currentState != STATE_JUMP){
            if(rs_rightfighter == 0 && rightFighter_currentState == STATE_FLUKE_HORSE_WALK){
                rightFighter_currentState = STATE_FLUKE_HORSE;
            }
            else if (rightFighter_currentState != STATE_FLUKE_HORSE){
                rightFighter_currentState = STATE_IDLE;
            }
        }
    }
    
animation_update:; // จัดการแรงโน้มถ่วงและการกระโดด
    if(!rightFighter_isGrounded){
        rightFighter_velocityY -= rightFighter_gravity * delta;
        rightFighter->y += rightFighter_velocityY * delta;
        
        // If jumping, set jump animation
        if (rightFighter_currentState != STATE_JUMP) { // Only set to jump if not already in a jump state
             rightFighter_currentState = STATE_JUMP;
        }
        
        // ตรวจสอบว่ากลับมาถึงพื้นหรือยัง (y = 0)
        if(rightFighter->y <= rightFighter_groundLevel){
            rightFighter->y = rightFighter_groundLevel;
            rightFighter_velocityY = 0;
            rightFighter_isGrounded = 1;
            rightFighter_currentState = STATE_IDLE;
        }
    }

    // Update animation based on current state
    if (rightFighter_currentState == STATE_BLOCK_STAND) {
        rightFighter_set_current_animation_state(block_stand);
        play_start_stop(rightFighter, rightFighter_anim, &rightFighter_currentFrameCounter, block_stand, rightFighter_facingRight, 0, rightFighter_block_stand_hold_frame);
    } else if (rightFighter_currentState == STATE_BLOCK_CROUCH) {
        rightFighter_set_current_animation_state(block_crouch);
        play_start_stop(rightFighter, rightFighter_anim, &rightFighter_currentFrameCounter, block_crouch, rightFighter_facingRight, 0, rightFighter_block_crouch_hold_frame);
    } else if (rightFighter_currentState == STATE_BLOCK_RELEASE) {
        int anim_index = (rightFighter_anim->anims[block_stand]->currentFrame > 0) ? block_stand : block_crouch;
        int start_frame = (anim_index == block_stand) ? rightFighter_block_stand_hold_frame : rightFighter_block_crouch_hold_frame;
        int end_frame = rightFighter_anim->anims[anim_index]->imageCount;
        play_animation_once(rightFighter, rightFighter_anim, &rightFighter_currentFrameCounter, anim_index, rightFighter_facingRight, start_frame, end_frame, rightFighter_on_block_release_complete);
    } else if (rightFighter_health <= 0 && rightFighter_currentState == STATE_FALL) {
        rightFighter_set_current_animation_state(fall);
        // Freeze on the first frame of the fall animation
        Animation* anim = rightFighter_anim->anims[fall + rightFighter_facingRight];
        set_image(rightFighter, anim->paths[0]);
    } else {
        rightFighter_set_current_animation_state(rightFighter_get_anim_index_from_state(rightFighter_currentState));
        // Play the current animation
        if (rightFighter_anim != NULL) {
            play_animation(rightFighter, rightFighter_anim, &rightFighter_currentFrameCounter, rightFighter_currentAnimIndex, rightFighter_facingRight);
        }
    }
}

void rightFighter_render(SDL_Renderer* renderer){
    render_entity(rightFighter, renderer, NULL);
}

void rightFighter_destroy(){
    destroy_entity(rightFighter);
}

void rightFighter_subtract_break(int val){
    rightFighter_breakGauge -= val;
}
void rightFighter_add_break(int val){
    rightFighter_breakGauge += val;
}
void rightFighter_subtract_health(int val){
    if (rightFighter_health <= 0) return; // Already knocked out

    rightFighter_health -= val;
    if (rightFighter_health <= 0) {
        rightFighter_health = 0;
        rightFighter_currentState = STATE_FALL;
    } else {
        rightFighter_currentState = STATE_DAMAGED;
    }
    rightFighter_stateTimer = 0.0f;
}
void rightFighter_add_health(int val){
    rightFighter_health += val;
}
void rightFighter_subtract_ultimate(int val){
    rightFighter_ultimateGauge -= val;
}
void rightFighter_add_ultimate(int val){
    rightFighter_ultimateGauge += val;
}