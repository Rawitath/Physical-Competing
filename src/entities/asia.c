#include "../entity.h"
#include "asia.h"
#include "../timesystem.h"
#include "../scene.h"
#include "../scenecontroller.h"
#include <stdio.h>
#include "../animation.h"

#include <SDL3/SDL.h>

void asia_start();
void asia_poll(SDL_Event* event);
void asia_loop();
void asia_render(SDL_Renderer* renderer);
void asia_destroy();

void set_animation(Animation* anim);

void asia_init(){
    asia = create_entity(
            "res/lucystar.png",
            &asia_start,
            &asia_poll,
            &asia_loop,
            &asia_render,
            &asia_destroy
        );
}

// Animation pointers
Animation* idleLeft = NULL;
Animation* idleRight = NULL;
Animation* walkLeft = NULL;
Animation* walkRight = NULL;
Animation* crouchLeft = NULL;
Animation* crouchRight = NULL;
Animation* jumpLeft = NULL;
Animation* jumpRight = NULL;
Animation* lightPunchLeft = NULL;
Animation* lightPunchRight = NULL;
Animation* heavyPunchLeft = NULL;
Animation* heavyPunchRight = NULL;
Animation* blockStandLeft = NULL;
Animation* blockStandRight = NULL;
Animation* blockCrouchLeft = NULL;
Animation* blockCrouchRight = NULL;
Animation* lowPunchLeft = NULL;
Animation* lowPunchRight = NULL;
Animation* skill1Left = NULL;
Animation* skill1Right = NULL;
Animation* skill2Left = NULL;
Animation* skill2Right = NULL;
Animation* skill3Left = NULL;
Animation* skill3Right = NULL;
Animation* ultimateLeft = NULL;
Animation* ultimateRight = NULL;

// State variables
typedef enum {
    STATE_IDLE,
    STATE_WALK,
    STATE_CROUCH,
    STATE_JUMP,
    STATE_LIGHT_PUNCH,
    STATE_HEAVY_PUNCH,
    STATE_BLOCK_STAND,
    STATE_BLOCK_CROUCH,
    STATE_LOW_PUNCH,
    STATE_SKILL1,
    STATE_SKILL2,
    STATE_SKILL3,
    STATE_ULTIMATE
} CharacterState;

CharacterState currentState = STATE_IDLE;
int facingRight = 0; // 0 = left, 1 = right
float velocityY = 0;
float gravity = 800.0f;
float jumpForce = 300.0f;
int isGrounded = 1;
float moveSpeed = 200.0f;

Animation* currentAnim = NULL;

// Combo system
#define MAX_COMBO_LENGTH 4
#define COMBO_TIMEOUT 2.0f

typedef enum {
    INPUT_NONE,
    INPUT_LIGHT,  // J or 2
    INPUT_HEAVY   // K or 3
} ComboInput;

ComboInput comboBuffer[MAX_COMBO_LENGTH];
int comboCount = 0;
float comboTimer = 0.0f;

void reset_combo() {
    comboCount = 0;
    comboTimer = 0.0f;
    for(int i = 0; i < MAX_COMBO_LENGTH; i++) {
        comboBuffer[i] = INPUT_NONE;
    }
}

void add_to_combo(ComboInput input) {
    if(comboCount < MAX_COMBO_LENGTH) {
        comboBuffer[comboCount] = input;
        comboCount++;
        comboTimer = 0.0f;
    }
}

int check_combo_pattern(ComboInput p1, ComboInput p2, ComboInput p3, ComboInput p4) {
    if(comboCount != 4) return 0;
    return (comboBuffer[0] == p1 && 
            comboBuffer[1] == p2 && 
            comboBuffer[2] == p3 && 
            comboBuffer[3] == p4);
}

int check_and_execute_skill() {
    // TODO: เพิ่มคอมโบสำหรับ asia ที่นี่
    // Skill 1: ???
    
    // Skill 2: ???
    
    // Skill 3: ???
    
    return 0;
}

void set_animation(Animation* anim) {
    if (currentAnim != anim) {
        currentAnim = anim;
        if (anim) {
            anim->currentFrame = 0;
        }
    }
}

void asia_start(){
    idleLeft = create_animation("res/fighters/asia/idle_left", 15);
    idleRight = create_animation("res/fighters/asia/idle_right", 15);
    walkLeft = create_animation("res/fighters/asia/walk_left", 15);
    walkRight = create_animation("res/fighters/asia/walk_right", 15);
    crouchLeft = create_animation("res/fighters/asia/crouch_left", 15);
    crouchRight = create_animation("res/fighters/asia/crouch_right", 15);
    jumpLeft = create_animation("res/fighters/asia/jump_left", 15);
    jumpRight = create_animation("res/fighters/asia/jump_right", 15);
    lightPunchLeft = create_animation("res/fighters/asia/light_punch_left", 20);
    lightPunchRight = create_animation("res/fighters/asia/light_punch_right", 20);
    heavyPunchLeft = create_animation("res/fighters/asia/heavy_punch_left", 20);
    heavyPunchRight = create_animation("res/fighters/asia/heavy_punch_right", 20);
    blockStandLeft = create_animation("res/fighters/asia/block_stand_left", 10);
    blockStandRight = create_animation("res/fighters/asia/block_stand_right", 10);
    blockCrouchLeft = create_animation("res/fighters/asia/block_crouch_left", 10);
    blockCrouchRight = create_animation("res/fighters/asia/block_crouch_right", 10);
    lowPunchLeft = create_animation("res/fighters/asia/low_punch_left", 20);
    lowPunchRight = create_animation("res/fighters/asia/low_punch_right", 20);
    skill1Left = create_animation("res/fighters/asia/skill1_left", 25);
    skill1Right = create_animation("res/fighters/asia/skill1_right", 25);
    skill2Left = create_animation("res/fighters/asia/skill2_left", 25);
    skill2Right = create_animation("res/fighters/asia/skill2_right", 25);
    skill3Left = create_animation("res/fighters/asia/skill3_left", 25);
    skill3Right = create_animation("res/fighters/asia/skill3_right", 25);
    ultimateLeft = create_animation("res/fighters/asia/ultimate_left", 30);
    ultimateRight = create_animation("res/fighters/asia/ultimate_right", 30);
    
    currentAnim = idleLeft;
    set_image(asia, currentAnim->paths[currentAnim->currentFrame]);
    reset_combo();
}

void asia_poll(SDL_Event* event){
    if(event->type == SDL_EVENT_KEY_DOWN){
        if((event->key.scancode == SDL_SCANCODE_W || 
            event->key.scancode == SDL_SCANCODE_UP) && isGrounded){
            currentState = STATE_JUMP;
            velocityY = jumpForce;
            isGrounded = 0;
        }
        
        if(event->key.scancode == SDL_SCANCODE_J || 
           event->key.scancode == SDL_SCANCODE_2){
            if(currentState != STATE_LIGHT_PUNCH && 
               currentState != STATE_HEAVY_PUNCH &&
               currentState != STATE_LOW_PUNCH &&
               currentState != STATE_SKILL1 &&
               currentState != STATE_SKILL2 &&
               currentState != STATE_SKILL3 &&
               currentState != STATE_ULTIMATE &&
               currentState != STATE_CROUCH &&
               currentState != STATE_BLOCK_CROUCH){
                
                add_to_combo(INPUT_LIGHT);
                
                if(!check_and_execute_skill()) {
                    currentState = STATE_LIGHT_PUNCH;
                    if(facingRight){
                        set_animation(lightPunchRight);
                    } else {
                        set_animation(lightPunchLeft);
                    }
                }
                
                printf("Combo: ");
                for(int i = 0; i < comboCount; i++) {
                    printf("%d ", comboBuffer[i]);
                }
                printf("\n");
            }
        }
        
        if(event->key.scancode == SDL_SCANCODE_K || 
           event->key.scancode == SDL_SCANCODE_3){
            if(currentState != STATE_LIGHT_PUNCH && 
               currentState != STATE_HEAVY_PUNCH &&
               currentState != STATE_LOW_PUNCH &&
               currentState != STATE_SKILL1 &&
               currentState != STATE_SKILL2 &&
               currentState != STATE_SKILL3 &&
               currentState != STATE_ULTIMATE &&
               currentState != STATE_CROUCH &&
               currentState != STATE_BLOCK_CROUCH){
                
                add_to_combo(INPUT_HEAVY);
                
                if(!check_and_execute_skill()) {
                    currentState = STATE_HEAVY_PUNCH;
                    if(facingRight){
                        set_animation(heavyPunchRight);
                    } else {
                        set_animation(heavyPunchLeft);
                    }
                }
                
                printf("Combo: ");
                for(int i = 0; i < comboCount; i++) {
                    printf("%d ", comboBuffer[i]);
                }
                printf("\n");
            }
        }
        
        if(event->key.scancode == SDL_SCANCODE_I || 
           event->key.scancode == SDL_SCANCODE_5){
            if(currentState != STATE_LIGHT_PUNCH && 
               currentState != STATE_HEAVY_PUNCH &&
               currentState != STATE_LOW_PUNCH &&
               currentState != STATE_SKILL1 &&
               currentState != STATE_SKILL2 &&
               currentState != STATE_SKILL3 &&
               currentState != STATE_ULTIMATE &&
               currentState != STATE_CROUCH &&
               currentState != STATE_BLOCK_CROUCH &&
               currentState != STATE_BLOCK_STAND){
                
                currentState = STATE_ULTIMATE;
                if(facingRight){
                    set_animation(ultimateRight);
                } else {
                    set_animation(ultimateLeft);
                }
                printf("ULTIMATE ACTIVATED!\n");
            }
        }
    }
}

float animTimer = 0;

void asia_loop(){
    float delta = get_delta();
    
    if(comboCount > 0) {
        comboTimer += delta;
        if(comboTimer >= COMBO_TIMEOUT) {
            printf("Combo timeout! Resetting...\n");
            reset_combo();
        }
    }
    
    if(animTimer < 1.0f / currentAnim->fps){
        animTimer += delta;
    } else {
        if(currentAnim->currentFrame < currentAnim->imageCount - 1){
            currentAnim->currentFrame++;
        } else {
            currentAnim->currentFrame = 0;
            
            if(currentState == STATE_LIGHT_PUNCH || 
               currentState == STATE_HEAVY_PUNCH ||
               currentState == STATE_SKILL1 ||
               currentState == STATE_SKILL2 ||
               currentState == STATE_SKILL3 ||
               currentState == STATE_ULTIMATE){
                currentState = STATE_IDLE;
            }
            if(currentState == STATE_LOW_PUNCH){
                currentState = STATE_CROUCH;
            }
        }
        set_image(asia, currentAnim->paths[currentAnim->currentFrame]);
        animTimer = 0;
    }
    
    const bool* keyState = SDL_GetKeyboardState(NULL);
    
    int isBlocking = keyState[SDL_SCANCODE_L] || keyState[SDL_SCANCODE_1];
    int isCrouching = keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_DOWN];
    
    if(currentState != STATE_LIGHT_PUNCH && 
       currentState != STATE_HEAVY_PUNCH && 
       currentState != STATE_LOW_PUNCH &&
       currentState != STATE_SKILL1 &&
       currentState != STATE_SKILL2 &&
       currentState != STATE_SKILL3 &&
       currentState != STATE_ULTIMATE){
        
        int moving = 0;
        
        if(isBlocking && isCrouching && isGrounded){
            currentState = STATE_BLOCK_CROUCH;
            if(facingRight){
                set_animation(blockCrouchRight);
            } else {
                set_animation(blockCrouchLeft);
            }
        }
        else if(isBlocking && isGrounded && currentState != STATE_JUMP){
            currentState = STATE_BLOCK_STAND;
            if(facingRight){
                set_animation(blockStandRight);
            } else {
                set_animation(blockStandLeft);
            }
        }
        else if(isCrouching && isGrounded){
            currentState = STATE_CROUCH;
            if(facingRight){
                set_animation(crouchRight);
            } else {
                set_animation(crouchLeft);
            }
            
            if(keyState[SDL_SCANCODE_J] || keyState[SDL_SCANCODE_2]){
                currentState = STATE_LOW_PUNCH;
                if(facingRight){
                    set_animation(lowPunchRight);
                } else {
                    set_animation(lowPunchLeft);
                }
            }
        }
        else if((keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_LEFT]) && !isCrouching){
            asia->x -= moveSpeed * delta;
            facingRight = 0;
            if(isGrounded && currentState != STATE_CROUCH){
                currentState = STATE_WALK;
                set_animation(walkLeft);
            }
            moving = 1;
        }
        else if((keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_RIGHT]) && !isCrouching){
            asia->x += moveSpeed * delta;
            facingRight = 1;
            if(isGrounded && currentState != STATE_CROUCH){
                currentState = STATE_WALK;
                set_animation(walkRight);
            }
            moving = 1;
        }
        else if(!moving && isGrounded && currentState != STATE_JUMP){
            currentState = STATE_IDLE;
            if(facingRight){
                set_animation(idleRight);
            } else {
                set_animation(idleLeft);
            }
        }
    }
    
    if(!isGrounded){
        velocityY -= gravity * delta;
        asia->y += velocityY * delta;
        
        if(facingRight){
            set_animation(jumpRight);
        } else {
            set_animation(jumpLeft);
        }
        
        if(asia->y <= 0){
            asia->y = 0;
            velocityY = 0;
            isGrounded = 1;
            currentState = STATE_IDLE;
        }
    }
}

void asia_render(SDL_Renderer* renderer){
    render_entity(asia, renderer, NULL);
}

void asia_destroy(){
    destroy_animation(idleLeft);
    destroy_animation(idleRight);
    destroy_animation(walkLeft);
    destroy_animation(walkRight);
    destroy_animation(crouchLeft);
    destroy_animation(crouchRight);
    destroy_animation(jumpLeft);
    destroy_animation(jumpRight);
    destroy_animation(lightPunchLeft);
    destroy_animation(lightPunchRight);
    destroy_animation(heavyPunchLeft);
    destroy_animation(heavyPunchRight);
    destroy_animation(blockStandLeft);
    destroy_animation(blockStandRight);
    destroy_animation(blockCrouchLeft);
    destroy_animation(blockCrouchRight);
    destroy_animation(lowPunchLeft);
    destroy_animation(lowPunchRight);
    destroy_animation(skill1Left);
    destroy_animation(skill1Right);
    destroy_animation(skill2Left);
    destroy_animation(skill2Right);
    destroy_animation(skill3Left);
    destroy_animation(skill3Right);
    destroy_animation(ultimateLeft);
    destroy_animation(ultimateRight);
    destroy_entity(asia);
}