#include "../entity.h"
#include "myentity.h"
#include "../timesystem.h"
#include "../scene.h"
#include "../scenecontroller.h"
#include <stdio.h>
#include "../animation.h"

#include <SDL3/SDL.h>

void myentity_start();
void myentity_poll(SDL_Event* event);
void myentity_loop();
void myentity_render(SDL_Renderer* renderer);
void myentity_destroy();

void myentity_init(){
    myentity = create_entity(
            "res/lucystar.png",
            &myentity_start,
            &myentity_poll,
            &myentity_loop,
            &myentity_render,
            &myentity_destroy
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
    STATE_LOW_PUNCH
} CharacterState;

CharacterState currentState = STATE_IDLE;
int facingRight = 0; // 0 = left, 1 = right
float velocityY = 0;
float gravity = 800.0f;
float jumpForce = 300.0f;
int isGrounded = 1;
float moveSpeed = 200.0f;

Animation* currentAnim = NULL;

void set_animation(Animation* anim) {
    if (currentAnim != anim) {
        currentAnim = anim;
        if (anim) {
            anim->currentFrame = 0;
        }
    }
}

void myentity_start(){
    // โหลด animations ทั้งหมด
    idleLeft = create_animation("res/fighters/bas/idle_left", 15);
    idleRight = create_animation("res/fighters/bas/idle_right", 15);
    walkLeft = create_animation("res/fighters/bas/walk_left", 15);
    walkRight = create_animation("res/fighters/bas/walk_right", 15);
    crouchLeft = create_animation("res/fighters/bas/crouch_left", 15);
    crouchRight = create_animation("res/fighters/bas/crouch_right", 15);
    jumpLeft = create_animation("res/fighters/bas/jump_left", 15);
    jumpRight = create_animation("res/fighters/bas/jump_right", 15);
    lightPunchLeft = create_animation("res/fighters/bas/light_punch_left", 20);
    lightPunchRight = create_animation("res/fighters/bas/light_punch_right", 20);
    heavyPunchLeft = create_animation("res/fighters/bas/heavy_punch_left", 20);
    heavyPunchRight = create_animation("res/fighters/bas/heavy_punch_right", 20);
    blockStandLeft = create_animation("res/fighters/bas/block_stand_left", 10);
    blockStandRight = create_animation("res/fighters/bas/block_stand_right", 10);
    blockCrouchLeft = create_animation("res/fighters/bas/block_crouch_left", 10);
    blockCrouchRight = create_animation("res/fighters/bas/block_crouch_right", 10);
    lowPunchLeft = create_animation("res/fighters/bas/low_punch_left", 20);
    lowPunchRight = create_animation("res/fighters/bas/low_punch_right", 20);
    
    currentAnim = idleLeft;
    set_image(myentity, currentAnim->paths[currentAnim->currentFrame]);
}

void myentity_poll(SDL_Event* event){
    if(event->type == SDL_EVENT_KEY_DOWN){
        // เปลี่ยนฉาก (ปิดการใช้งานชั่วคราวเพื่อไม่ให้ขัดกับการบล็อก)
        // if(event->key.scancode == SDL_SCANCODE_D){
        //     sc_load_scene(1);
        //     return;
        // }
        
        // กระโดด (W หรือ ลูกศรขึ้น)
        if((event->key.scancode == SDL_SCANCODE_W || 
            event->key.scancode == SDL_SCANCODE_UP) && isGrounded){
            currentState = STATE_JUMP;
            velocityY = jumpForce;
            isGrounded = 0;
        }
        
        // ต่อยเบา (J หรือ 2) - ยืนเท่านั้น
        if(event->key.scancode == SDL_SCANCODE_J || 
           event->key.scancode == SDL_SCANCODE_2){
            if(currentState != STATE_LIGHT_PUNCH && 
               currentState != STATE_HEAVY_PUNCH &&
               currentState != STATE_LOW_PUNCH &&
               currentState != STATE_CROUCH &&
               currentState != STATE_BLOCK_CROUCH){
                currentState = STATE_LIGHT_PUNCH;
                if(facingRight){
                    set_animation(lightPunchRight);
                } else {
                    set_animation(lightPunchLeft);
                }
            }
        }
        
        // ต่อยหนัก (K หรือ 3) - ยืนเท่านั้น
        if(event->key.scancode == SDL_SCANCODE_K || 
           event->key.scancode == SDL_SCANCODE_3){
            if(currentState != STATE_LIGHT_PUNCH && 
               currentState != STATE_HEAVY_PUNCH &&
               currentState != STATE_LOW_PUNCH &&
               currentState != STATE_CROUCH &&
               currentState != STATE_BLOCK_CROUCH){
                currentState = STATE_HEAVY_PUNCH;
                if(facingRight){
                    set_animation(heavyPunchRight);
                } else {
                    set_animation(heavyPunchLeft);
                }
            }
        }
    }
}

float animTimer = 0;

void myentity_loop(){
    float delta = get_delta();
    
    // จัดการ animation timer
    if(animTimer < 1.0f / currentAnim->fps){
        animTimer += delta;
    } else {
        if(currentAnim->currentFrame < currentAnim->imageCount - 1){
            currentAnim->currentFrame++;
        } else {
            currentAnim->currentFrame = 0;
            
            // ถ้าจบ animation การโจมตี กลับไป idle หรือ crouch
            if(currentState == STATE_LIGHT_PUNCH || 
               currentState == STATE_HEAVY_PUNCH){
                currentState = STATE_IDLE;
            }
            if(currentState == STATE_LOW_PUNCH){
                currentState = STATE_CROUCH;
            }
        }
        set_image(myentity, currentAnim->paths[currentAnim->currentFrame]);
        animTimer = 0;
    }
    
    // อ่านค่า keyboard state
    const bool* keyState = SDL_GetKeyboardState(NULL);
    
    // ตรวจสอบการกดปุ่มบล็อก (L หรือ 1)
    int isBlocking = keyState[SDL_SCANCODE_L] || keyState[SDL_SCANCODE_1];
    
    // ตรวจสอบการกดปุ่มนั่ง (S หรือ ลูกศรลง)
    int isCrouching = keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_DOWN];
    
    // ถ้าไม่ได้กำลังโจมตี ให้สามารถเคลื่อนไหวได้
    if(currentState != STATE_LIGHT_PUNCH && 
       currentState != STATE_HEAVY_PUNCH && 
       currentState != STATE_LOW_PUNCH){
        
        int moving = 0;
        
        // ถ้ากด Block + Crouch = บล็อกแบบนั่ง
        if(isBlocking && isCrouching && isGrounded){
            currentState = STATE_BLOCK_CROUCH;
            if(facingRight){
                set_animation(blockCrouchRight);
            } else {
                set_animation(blockCrouchLeft);
            }
        }
        // ถ้ากด Block เฉยๆ = บล็อกแบบยืน
        else if(isBlocking && isGrounded && currentState != STATE_JUMP){
            currentState = STATE_BLOCK_STAND;
            if(facingRight){
                set_animation(blockStandRight);
            } else {
                set_animation(blockStandLeft);
            }
        }
        // ถ้ากด Crouch เฉยๆ
        else if(isCrouching && isGrounded){
            currentState = STATE_CROUCH;
            if(facingRight){
                set_animation(crouchRight);
            } else {
                set_animation(crouchLeft);
            }
            
            // เช็คว่ากดปุ่มโจมตีในขณะนั่งหรือไม่
            if(keyState[SDL_SCANCODE_J] || keyState[SDL_SCANCODE_2]){
                currentState = STATE_LOW_PUNCH;
                if(facingRight){
                    set_animation(lowPunchRight);
                } else {
                    set_animation(lowPunchLeft);
                }
            }
        }
        // เดินซ้าย (A หรือ ลูกศรซ้าย)
        else if((keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_LEFT]) && !isCrouching){
            myentity->x -= moveSpeed * delta;
            facingRight = 0;
            if(isGrounded && currentState != STATE_CROUCH){
                currentState = STATE_WALK;
                set_animation(walkLeft);
            }
            moving = 1;
        }
        // เดินขวา (D หรือ ลูกศรขวา)
        else if((keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_RIGHT]) && !isCrouching){
            myentity->x += moveSpeed * delta;
            facingRight = 1;
            if(isGrounded && currentState != STATE_CROUCH){
                currentState = STATE_WALK;
                set_animation(walkRight);
            }
            moving = 1;
        }
        // ถ้าไม่กดปุ่มใดๆ และอยู่บนพื้น ให้ idle
        else if(!moving && isGrounded && currentState != STATE_JUMP){
            currentState = STATE_IDLE;
            if(facingRight){
                set_animation(idleRight);
            } else {
                set_animation(idleLeft);
            }
        }
    }
    
    // จัดการแรงโน้มถ่วงและการกระโดด
    if(!isGrounded){
        velocityY -= gravity * delta;
        myentity->y += velocityY * delta;
        
        if(facingRight){
            set_animation(jumpRight);
        } else {
            set_animation(jumpLeft);
        }
        
        // ตรวจสอบว่ากลับมาถึงพื้นหรือยัง (y = 0)
        if(myentity->y <= 0){
            myentity->y = 0;
            velocityY = 0;
            isGrounded = 1;
            currentState = STATE_IDLE;
        }
    }
}

void myentity_render(SDL_Renderer* renderer){
    render_entity(myentity, renderer, NULL);
}

void myentity_destroy(){
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
    destroy_entity(myentity);
}