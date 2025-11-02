#include "../entity.h"
#include "leftFighter.h"
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
#include "lefthealthbar.h"
#include "leftultibar.h"

void leftFighter_start();
void leftFighter_poll(SDL_Event* event);
void leftFighter_loop();
void leftFighter_render(SDL_Renderer* renderer);

float leftFighter_x = 0;
float leftFighter_groundLevel = -3.5;

void leftFighter_init(){
    leftFighter = create_entity(
            NULL,
            &leftFighter_start,
            &leftFighter_poll,
            &leftFighter_loop,
            &leftFighter_render,
            &leftFighter_destroy
        );
    leftFighter->w *= 0.55;
    leftFighter->h *= 0.55;
    // leftFighter_anim will be set in leftFighter_start
}

// Animation pointers
FighterAnim* leftFighter_anim = NULL;

CharacterState leftFighter_currentState = STATE_IDLE;
// Animation state variables
int leftFighter_currentAnimIndex = idle;
int leftFighter_facingRight = 1; // 0 = left, 1 = right
float leftFighter_velocityY = 0;
float leftFighter_gravity = 80.0;
float leftFighter_jumpForce = 30.0;
int leftFighter_isGrounded = 1;
float leftFighter_moveSpeed = 9.0;
PlayerKeybind leftFighter_keybind;
float leftFighter_currentFrameCounter = 0;

//Stats
int leftFighter_health = 100;
int leftFighter_ultimateGauge = 0;
int leftFighter_breakGauge = 100;
int leftFighter_isFrozen = 0;

// State timer
float leftFighter_stateTimer = 0.0;
float leftFighter_light_attack_timeout = 0.3;
float leftFighter_heavy_attack_timeout = 0.6;
float leftFighter_crouch_light_attack_timeout = 0.4;
float leftFighter_crouch_heavy_attack_timeout = 0.7;
float leftFighter_fall_timeout = 5;
float leftFighter_skill1_time = 6;
float leftFighter_skill2_time = 6;
float leftFighter_skill3_time = 6;
float leftFighter_ultimate_time = 4;
float leftFighter_damaged_timeout = 2;
float leftFighter_fluke_horse_timeout = 10;


// Animation segment points
int leftFighter_block_stand_hold_frame = 0;
int leftFighter_block_crouch_hold_frame = 0;

// Combo system
#define MAX_COMBO_LENGTH 4
#define COMBO_TIMEOUT 5.0f

PlayerInput leftFighter_comboBuffer[MAX_COMBO_LENGTH];
int leftFighter_comboCount = 0;
float leftFighter_comboTimer = 5.0f;

void leftFighter_reset_combo() {
    leftFighter_comboCount = 0;
    leftFighter_comboTimer = 0.0f;
    for(int i = 0; i < MAX_COMBO_LENGTH; i++) {
        leftFighter_comboBuffer[i] = INPUT_NONE;
    }
}

void leftFighter_add_to_combo(PlayerInput input) {
    if(leftFighter_comboCount < MAX_COMBO_LENGTH) {
        leftFighter_comboBuffer[leftFighter_comboCount] = input;
        leftFighter_comboCount++;
        leftFighter_comboTimer = 0.0f; // Reset timer when new input added
    }
}

int leftFighter_check_combo_pattern(PlayerInput p1, PlayerInput p2, PlayerInput p3, PlayerInput p4) {
    if(leftFighter_comboCount != 4) return 0;
    return (leftFighter_comboBuffer[0] == p1 && 
            leftFighter_comboBuffer[1] == p2 && 
            leftFighter_comboBuffer[2] == p3 && 
            leftFighter_comboBuffer[3] == p4);
}

int leftFighter_check_and_execute_skill() {
    // TODO: Implement actual skill combos for leftFighter
    // Example: Skill 3: Light, Heavy, Light, Heavy
    if(leftFighter_check_combo_pattern(allFighters[rs_leftfighter]->skill1Keys[0],
                           allFighters[rs_leftfighter]->skill1Keys[1],
                           allFighters[rs_leftfighter]->skill1Keys[2],
                           allFighters[rs_leftfighter]->skill1Keys[3])) {
        leftFighter_currentState = STATE_SKILL1;
        allFighters[rs_leftfighter]->skill1(leftFighter, leftFighter_facingRight);
        leftFighter_stateTimer = 0.0f;
        leftFighter_reset_combo();
        return 1;
    }
    if(leftFighter_check_combo_pattern(allFighters[rs_leftfighter]->skill2Keys[0],
                           allFighters[rs_leftfighter]->skill2Keys[1],
                           allFighters[rs_leftfighter]->skill2Keys[2],
                           allFighters[rs_leftfighter]->skill2Keys[3])) {
        leftFighter_currentState = STATE_SKILL2;
        allFighters[rs_leftfighter]->skill2(leftFighter, leftFighter_facingRight);
        leftFighter_stateTimer = 0.0f;
        leftFighter_reset_combo();
        return 1;
    }
    if(leftFighter_check_combo_pattern(allFighters[rs_leftfighter]->skill3Keys[0],
                           allFighters[rs_leftfighter]->skill3Keys[1],
                           allFighters[rs_leftfighter]->skill3Keys[2],
                           allFighters[rs_leftfighter]->skill3Keys[3])) {
        leftFighter_currentState = STATE_SKILL3;
        allFighters[rs_leftfighter]->skill3(leftFighter, leftFighter_facingRight);
        leftFighter_stateTimer = 0.0f;
        leftFighter_reset_combo();
        return 1;
    }
    return 0;
}

void leftFighter_set_current_animation_state(int newAnimIndex) {
    if (leftFighter_currentAnimIndex != newAnimIndex) {
        leftFighter_currentAnimIndex = newAnimIndex;
        reset_animation_frame(leftFighter_anim, newAnimIndex + leftFighter_facingRight);
        leftFighter_currentFrameCounter = 0; // Reset frame counter when animation changes
    }
}

int leftFighter_get_anim_index_from_state(CharacterState state) {
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
void leftFighter_setup_player(){
    leftFighter_anim = allFighters[rs_leftfighter]->fighterAnim;
    leftFighter_currentAnimIndex = idle;
    leftFighter_gravity = 80.0f;
    leftFighter_jumpForce = 30.0f;
    leftFighter_moveSpeed = allFighters[rs_leftfighter]->speed;
    leftFighter_light_attack_timeout = allFighters[rs_leftfighter]->lightAttackTime;
    leftFighter_heavy_attack_timeout = allFighters[rs_leftfighter]->heavyAttackTime;
    leftFighter_crouch_light_attack_timeout = allFighters[rs_leftfighter]->crouchLightAttackTime;
    leftFighter_crouch_heavy_attack_timeout = allFighters[rs_leftfighter]->crouchHeavyAttackTime;
    leftFighter_skill1_time = allFighters[rs_leftfighter]->skill1Time;
    leftFighter_skill2_time = allFighters[rs_leftfighter]->skill2Time;
    leftFighter_skill3_time = allFighters[rs_leftfighter]->skill3Time;
    leftFighter_ultimate_time = allFighters[rs_leftfighter]->ultimateTime;
}

void leftFighter_start(){
    leftFighter_health = 100;
    leftFighter_ultimateGauge = 0;
    leftFighter_breakGauge = 100;
    leftFighter->x = -5;

    leftFighter_reset_combo();
    // Initialize keybinds (example default for Player 1)
    leftFighter_keybind._left = SDL_SCANCODE_A;
    leftFighter_keybind._right = SDL_SCANCODE_D;
    leftFighter_keybind._jump = SDL_SCANCODE_W;
    leftFighter_keybind._crouch = SDL_SCANCODE_S;
    leftFighter_keybind._light_punch = SDL_SCANCODE_J;
    leftFighter_keybind._heavy_punch = SDL_SCANCODE_K;
    leftFighter_keybind._ultimate = SDL_SCANCODE_I;
    leftFighter_keybind._block = SDL_SCANCODE_L;

    // Assign a FighterAnim (e.g., Fluke's animations)
    // In a real game, this would be determined by player selection
    leftFighter_currentState = STATE_IDLE;
    leftFighter->y = leftFighter_groundLevel;
    leftFighter_setup_player();

    if (leftFighter_anim && leftFighter_anim->anims[block_stand]) {
        leftFighter_block_stand_hold_frame = leftFighter_anim->anims[block_stand]->imageCount / 2;
        leftFighter_block_crouch_hold_frame = leftFighter_anim->anims[block_crouch]->imageCount / 2;
    }

    // leftFighter_set_current_animation_state(idle);
}

void leftFighter_set_frozen(int frozen) {
    leftFighter_isFrozen = frozen;
}

void leftFighter_poll(SDL_Event* event){
    if(event->type == SDL_EVENT_KEY_DOWN){
        // กระโดด (W หรือ ลูกศรขึ้น)
        if((event->key.scancode == leftFighter_keybind._jump) && leftFighter_isGrounded){
            if(leftFighter_currentState != STATE_SKILL1 &&
               leftFighter_currentState != STATE_SKILL2 &&
               leftFighter_currentState != STATE_SKILL3 &&
               leftFighter_currentState != STATE_ULTIMATE &&
               leftFighter_currentState != STATE_CROUCH &&
               leftFighter_currentState != STATE_FALL &&
               !leftFighter_isFrozen && leftFighter_currentState != STATE_FLUKE_HORSE && leftFighter_currentState != STATE_FLUKE_HORSE_WALK){
            leftFighter_add_to_combo(INPUT_JUMP);
            if(!leftFighter_check_and_execute_skill()){
                leftFighter_currentState = STATE_JUMP;
                leftFighter_velocityY = leftFighter_jumpForce;
                leftFighter_isGrounded = 0;
            }
        }
        }
        if(event->key.scancode == leftFighter_keybind._block){
            if(leftFighter_currentState != STATE_LIGHT_PUNCH && 
               leftFighter_currentState != STATE_HEAVY_PUNCH &&
               leftFighter_currentState != STATE_BLOCK_RELEASE &&
               leftFighter_currentState != STATE_LOW_LIGHT_PUNCH &&
               leftFighter_currentState != STATE_LOW_HEAVY_PUNCH &&
               leftFighter_currentState != STATE_SKILL1 &&
               leftFighter_currentState != STATE_SKILL2 &&
               leftFighter_currentState != STATE_SKILL3 &&
               leftFighter_currentState != STATE_ULTIMATE &&
               leftFighter_currentState != STATE_FALL){
            leftFighter_add_to_combo(INPUT_BLOCK);
            leftFighter_check_and_execute_skill();
               }
        }
        
        // ต่อยเบา (J หรือ 2) - ยืนเท่านั้น
        if(event->key.scancode == leftFighter_keybind._light_punch){
            if(leftFighter_currentState != STATE_LIGHT_PUNCH && 
               leftFighter_currentState != STATE_HEAVY_PUNCH &&
               leftFighter_currentState != STATE_BLOCK_RELEASE &&
               leftFighter_currentState != STATE_LOW_LIGHT_PUNCH &&
               leftFighter_currentState != STATE_LOW_HEAVY_PUNCH &&
               leftFighter_currentState != STATE_SKILL1 &&
               leftFighter_currentState != STATE_SKILL2 &&
               leftFighter_currentState != STATE_SKILL3 &&
               leftFighter_currentState != STATE_ULTIMATE &&
               leftFighter_currentState != STATE_CROUCH &&
               leftFighter_currentState != STATE_FALL &&
               leftFighter_currentState != STATE_BLOCK_CROUCH){
                
                // Add to combo
                leftFighter_add_to_combo(INPUT_LIGHT);
                
                // Check if we can execute a skill
                if(!leftFighter_check_and_execute_skill()) {
                    // Normal light punch
                    leftFighter_currentState = STATE_LIGHT_PUNCH;
                }                
            }
        }
        
        // ต่อยหนัก (K หรือ 3) - ยืนเท่านั้น
        if(event->key.scancode == leftFighter_keybind._heavy_punch){
            if(leftFighter_currentState != STATE_LIGHT_PUNCH && 
               leftFighter_currentState != STATE_HEAVY_PUNCH &&
               leftFighter_currentState != STATE_BLOCK_RELEASE &&
               leftFighter_currentState != STATE_LOW_LIGHT_PUNCH &&
               leftFighter_currentState != STATE_LOW_HEAVY_PUNCH &&
               leftFighter_currentState != STATE_SKILL1 &&
               leftFighter_currentState != STATE_SKILL2 &&
               leftFighter_currentState != STATE_SKILL3 &&
               leftFighter_currentState != STATE_ULTIMATE &&
               leftFighter_currentState != STATE_CROUCH &&
               leftFighter_currentState != STATE_FALL &&
               leftFighter_currentState != STATE_BLOCK_CROUCH){
                
                // Add to combo
                leftFighter_add_to_combo(INPUT_HEAVY);
                
                // Check if we can execute a skill
                if(!leftFighter_check_and_execute_skill()) {
                    // Normal heavy punch
                    leftFighter_currentState = STATE_HEAVY_PUNCH;
                }                
            }
        }
        
        // Ultimate (I หรือ 5) - ไม่สามารถบล็อกได้
        if(leftFighter_ultimateGauge >= 100 && event->key.scancode == leftFighter_keybind._ultimate){
            if(leftFighter_currentState != STATE_LIGHT_PUNCH && 
               leftFighter_currentState != STATE_HEAVY_PUNCH &&
               leftFighter_currentState != STATE_BLOCK_RELEASE &&
               leftFighter_currentState != STATE_LOW_LIGHT_PUNCH &&
               leftFighter_currentState != STATE_LOW_HEAVY_PUNCH &&
               leftFighter_currentState != STATE_SKILL1 &&
               leftFighter_currentState != STATE_SKILL2 &&
               leftFighter_currentState != STATE_SKILL3 &&
               leftFighter_currentState != STATE_ULTIMATE &&
               leftFighter_currentState != STATE_CROUCH &&
               leftFighter_currentState != STATE_BLOCK_CROUCH &&
               leftFighter_currentState != STATE_FALL &&
               leftFighter_currentState != STATE_BLOCK_STAND){
                
                leftFighter_currentState = STATE_ULTIMATE;
                leftFighter_ultimateGauge = 0;
                leftFighter_stateTimer = 0.0f;
                allFighters[rs_leftfighter]->ultimate(leftFighter);
            }
        
                // printf("ULTIMATE ACTIVATED!\n");e
            }
        
    }
    else if (event->type == SDL_EVENT_KEY_UP) {
        if (event->key.scancode == leftFighter_keybind._block) {
            if (leftFighter_currentState == STATE_BLOCK_STAND || leftFighter_currentState == STATE_BLOCK_CROUCH) {
                leftFighter_currentState = STATE_BLOCK_RELEASE;
            }
        }
    }
}

void leftFighter_on_block_release_complete() {
        leftFighter_currentState = STATE_IDLE;
    }

void leftFighter_on_fall_anim_complete() {
    // This function can be used if you want something to happen when the fall animation finishes
    // For now, we'll just freeze the animation, so this can be empty.
}

void leftFighter_loop(){
    float delta = get_delta();
    lefthealthbar_set_health(leftFighter_health);
    leftultibar_set_health(leftFighter_ultimateGauge);
    // printf("%d, %d, %d, %d\n", leftFighter_comboBuffer[0], leftFighter_comboBuffer[1], leftFighter_comboBuffer[2], leftFighter_comboBuffer[3]);

    if (leftFighter_isFrozen) {
        if(leftFighter_health <= 0){
            leftFighter_currentState = STATE_FALL;
            goto animation_update;
        }
        leftFighter_currentState = STATE_IDLE;
        goto animation_update;
    }
    
    if (leftFighter_health <= 0) goto animation_update;
    //Fall logic
    if(leftFighter_currentState != STATE_FALL && leftFighter_breakGauge < 1){
        leftFighter_currentState = STATE_FALL;
        leftFighter_stateTimer = 0.0f; // Reset timer when entering fall state
    } else if (leftFighter_currentState == STATE_FALL) {
        // The rest of the loop is skipped while in STATE_FALL
    }


    // Update combo timer
    if(leftFighter_comboCount > 0) {
        leftFighter_comboTimer += delta;
        if(leftFighter_comboTimer >= COMBO_TIMEOUT) {
            // printf("Combo timeout! Resetting...\n");
            leftFighter_reset_combo();
        }
    }

    // Handle state timer for attacks
    if (leftFighter_currentState == STATE_LIGHT_PUNCH) {
        leftFighter_stateTimer += delta;
        if (leftFighter_stateTimer >= leftFighter_light_attack_timeout) {
            leftFighter_currentState = STATE_IDLE;
            leftFighter_stateTimer = 0.0f;
        }
    } else if (leftFighter_currentState == STATE_HEAVY_PUNCH) {
        leftFighter_stateTimer += delta;
        if (leftFighter_stateTimer >= leftFighter_heavy_attack_timeout) {
            leftFighter_currentState = STATE_IDLE;
            leftFighter_stateTimer = 0.0f;
        }
    } else if (leftFighter_currentState == STATE_LOW_LIGHT_PUNCH) {
        leftFighter_stateTimer += delta;
        if (leftFighter_stateTimer >= leftFighter_crouch_light_attack_timeout){
            leftFighter_currentState = STATE_CROUCH; // Return to crouch after low punch
            leftFighter_stateTimer = 0.0f;
        }
    } else if (leftFighter_currentState == STATE_LOW_HEAVY_PUNCH) {
        leftFighter_stateTimer += delta;
        if (leftFighter_stateTimer >= leftFighter_crouch_heavy_attack_timeout) {
            leftFighter_currentState = STATE_CROUCH; // Return to crouch after low heavy punch
            leftFighter_stateTimer = 0.0f;
        }
    } else if (leftFighter_currentState == STATE_FALL) {
        leftFighter_stateTimer += delta;
        if (leftFighter_stateTimer >= leftFighter_fall_timeout) {
            leftFighter_currentState = STATE_IDLE;
            leftFighter_breakGauge = 100;
            leftFighter_stateTimer = 0.0f;
        }
    } else if (leftFighter_currentState == STATE_DAMAGED){
        leftFighter_stateTimer += delta;
        if(leftFighter_stateTimer >= leftFighter_damaged_timeout){
            leftFighter_currentState = STATE_IDLE;
            leftFighter_stateTimer = 0.0f;
        }
    }
    else if (leftFighter_currentState == STATE_SKILL1) {
        leftFighter_stateTimer += delta;
        if (leftFighter_stateTimer >= leftFighter_skill1_time) {
            leftFighter_currentState = STATE_IDLE;
            leftFighter_stateTimer = 0.0f;
        }
    } else if (leftFighter_currentState == STATE_SKILL2) {
        leftFighter_stateTimer += delta;
        if (leftFighter_stateTimer >= leftFighter_skill2_time) {
            leftFighter_currentState = STATE_IDLE;
            leftFighter_stateTimer = 0.0f;
        }
    } else if (leftFighter_currentState == STATE_SKILL3) {
        leftFighter_stateTimer += delta;
        if (leftFighter_stateTimer >= leftFighter_skill3_time) {
            leftFighter_currentState = STATE_IDLE;
            leftFighter_stateTimer = 0.0f;
        }
    } else if (leftFighter_currentState == STATE_ULTIMATE) {
        leftFighter_stateTimer += delta;
        if (leftFighter_stateTimer >= leftFighter_ultimate_time) {
            if(rs_leftfighter != 0){
                leftFighter_currentState = STATE_IDLE;
                leftFighter_stateTimer = 0.0f;
            }
            else{
                leftFighter_currentState = STATE_FLUKE_HORSE;
                leftFighter_stateTimer = 0.0f;
            }
            
        }
    }
    else if (leftFighter_currentState == STATE_FLUKE_HORSE) {
        leftFighter_stateTimer += delta;
        if (leftFighter_stateTimer >= leftFighter_fluke_horse_timeout) {
            leftFighter_currentState = STATE_IDLE;
            leftFighter_stateTimer = 0.0f;
        }
    }
    else {
        // Reset timer if not in an attack state
        leftFighter_stateTimer = 0.0f;
    }
    
    // อ่านค่า keyboard state
    const bool* keyState = SDL_GetKeyboardState(NULL);
    
    // ตรวจสอบการกดปุ่มบล็อก (L หรือ 1)
    int isBlocking = keyState[leftFighter_keybind._block];
    
    // ตรวจสอบการกดปุ่มนั่ง (S หรือ ลูกศรลง)
    int isCrouching = keyState[leftFighter_keybind._crouch];
    
    // ถ้าไม่ได้กำลังโจมตีหรือใช้สกิล ให้สามารถเคลื่อนไหวได้
    if(leftFighter_currentState != STATE_LIGHT_PUNCH && 
       leftFighter_currentState != STATE_HEAVY_PUNCH && 
       leftFighter_currentState != STATE_BLOCK_RELEASE &&
       leftFighter_currentState != STATE_LOW_LIGHT_PUNCH &&
       leftFighter_currentState != STATE_LOW_HEAVY_PUNCH &&
       leftFighter_currentState != STATE_SKILL1 &&
       leftFighter_currentState != STATE_SKILL2 &&
       leftFighter_currentState != STATE_SKILL3 &&
       leftFighter_currentState != STATE_FALL &&
       leftFighter_currentState != STATE_DAMAGED &&
       leftFighter_currentState != STATE_ULTIMATE){
        
        int moving = 0;
        
        // Determine character state based on input
        if(isBlocking && isCrouching && leftFighter_isGrounded) {
            leftFighter_currentState = STATE_BLOCK_CROUCH;
        }
        else if(isBlocking && leftFighter_isGrounded && leftFighter_currentState != STATE_JUMP){
            leftFighter_currentState = STATE_BLOCK_STAND;
        }
        // ถ้ากด Crouch เฉยๆ
        else if(isCrouching && leftFighter_isGrounded){
            leftFighter_currentState = STATE_CROUCH;
            
            // เช็คว่ากดปุ่มโจมตีในขณะนั่งหรือไม่
            if(keyState[leftFighter_keybind._light_punch]){
                leftFighter_currentState = STATE_LOW_LIGHT_PUNCH;
            }
            else if(keyState[leftFighter_keybind._heavy_punch]){
                leftFighter_currentState = STATE_LOW_HEAVY_PUNCH;
            }
        }
        // เดินซ้าย (A หรือ ลูกศรซ้าย)
        else if((keyState[leftFighter_keybind._left]) && !isCrouching){
            leftFighter->x -= leftFighter_moveSpeed * delta;
            leftFighter_facingRight = 0;
            if(leftFighter_isGrounded && leftFighter_currentState != STATE_CROUCH){
                if(rs_leftfighter == 0 && (leftFighter_currentState == STATE_FLUKE_HORSE || leftFighter_currentState == STATE_FLUKE_HORSE_WALK)){
                    leftFighter_currentState = STATE_FLUKE_HORSE_WALK;
                }
                else{
                    leftFighter_currentState = STATE_WALK;
                }
            }
            moving = 1;
        }
        // เดินขวา (D หรือ ลูกศรขวา)
        else if((keyState[leftFighter_keybind._right]) && !isCrouching){
            leftFighter->x += leftFighter_moveSpeed * delta;
            leftFighter_facingRight = 1;
            if(leftFighter_isGrounded && leftFighter_currentState != STATE_CROUCH){
                if(rs_leftfighter == 0 && (leftFighter_currentState == STATE_FLUKE_HORSE || leftFighter_currentState == STATE_FLUKE_HORSE_WALK)){
                    leftFighter_currentState = STATE_FLUKE_HORSE_WALK;
                }
                else{
                    leftFighter_currentState = STATE_WALK;
                }
            }
            moving = 1;
        }
        // ถ้าไม่กดปุ่มใดๆ และอยู่บนพื้น ให้ idle
        else if(!moving && leftFighter_isGrounded && leftFighter_currentState != STATE_JUMP){
            if(rs_leftfighter == 0 && leftFighter_currentState == STATE_FLUKE_HORSE_WALK){
                leftFighter_currentState = STATE_FLUKE_HORSE;
            }
            else if (leftFighter_currentState != STATE_FLUKE_HORSE){
                leftFighter_currentState = STATE_IDLE;
            }
        }
    }
    
animation_update:; // จัดการแรงโน้มถ่วงและการกระโดด
    if(!leftFighter_isGrounded){
        leftFighter_velocityY -= leftFighter_gravity * delta;
        leftFighter->y += leftFighter_velocityY * delta;
        
        // If jumping, set jump animation
        if (leftFighter_currentState != STATE_JUMP) { // Only set to jump if not already in a jump state
             leftFighter_currentState = STATE_JUMP;
        }
        
        // ตรวจสอบว่ากลับมาถึงพื้นหรือยัง (y = 0)
        if(leftFighter->y <= leftFighter_groundLevel){
            leftFighter->y = leftFighter_groundLevel;
            leftFighter_velocityY = 0;
            leftFighter_isGrounded = 1;
            leftFighter_currentState = STATE_IDLE;
        }
    }

    // Update animation based on current state
    if (leftFighter_currentState == STATE_BLOCK_STAND) {
        leftFighter_set_current_animation_state(block_stand);
        play_start_stop(leftFighter, leftFighter_anim, &leftFighter_currentFrameCounter, block_stand, leftFighter_facingRight, 0, leftFighter_block_stand_hold_frame);
    } else if (leftFighter_currentState == STATE_BLOCK_CROUCH) {
        leftFighter_set_current_animation_state(block_crouch);
        play_start_stop(leftFighter, leftFighter_anim, &leftFighter_currentFrameCounter, block_crouch, leftFighter_facingRight, 0, leftFighter_block_crouch_hold_frame);
    } else if (leftFighter_currentState == STATE_BLOCK_RELEASE) {
        int anim_index = (leftFighter_anim->anims[block_stand]->currentFrame > 0) ? block_stand : block_crouch;
        int start_frame = (anim_index == block_stand) ? leftFighter_block_stand_hold_frame : leftFighter_block_crouch_hold_frame;
        int end_frame = leftFighter_anim->anims[anim_index]->imageCount;
        play_animation_once(leftFighter, leftFighter_anim, &leftFighter_currentFrameCounter, anim_index, leftFighter_facingRight, start_frame, end_frame, leftFighter_on_block_release_complete);
    } else if (leftFighter_health <= 0 && leftFighter_currentState == STATE_FALL) {
        leftFighter_set_current_animation_state(fall);
        // Freeze on the first frame of the fall animation
        Animation* anim = leftFighter_anim->anims[fall + leftFighter_facingRight];
        set_image(leftFighter, anim->paths[0]);
    } else {
        leftFighter_set_current_animation_state(leftFighter_get_anim_index_from_state(leftFighter_currentState));
        // Play the current animation
        if (leftFighter_anim != NULL) {
            play_animation(leftFighter, leftFighter_anim, &leftFighter_currentFrameCounter, leftFighter_currentAnimIndex, leftFighter_facingRight);
        }
    }
}

void leftFighter_render(SDL_Renderer* renderer){
    render_entity(leftFighter, renderer, NULL);
}

void leftFighter_destroy(){
    destroy_entity(leftFighter);
}

void leftFighter_subtract_break(int val){
    leftFighter_breakGauge -= val;
}
void leftFighter_add_break(int val){
    leftFighter_breakGauge += val;
}
void leftFighter_subtract_health(int val){
    if (leftFighter_health <= 0) return; // Already knocked out

    leftFighter_health -= val;
    if (leftFighter_health <= 0) {
        leftFighter_health = 0;
        leftFighter_currentState = STATE_FALL;
    } else {
        leftFighter_currentState = STATE_DAMAGED;
    }
    leftFighter_stateTimer = 0.0f;
}
void leftFighter_add_health(int val){
    leftFighter_health += val;
}
void leftFighter_subtract_ultimate(int val){
    leftFighter_ultimateGauge -= val;
}
void leftFighter_add_ultimate(int val){
    leftFighter_ultimateGauge += val;
}