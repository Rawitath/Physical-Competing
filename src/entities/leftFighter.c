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
int leftFighter_facingRight = 0; // 0 = left, 1 = right
float leftFighter_velocityY = 0;
float leftFighter_gravity = 80.0f;
float leftFighter_jumpForce = 30.0f;
int leftFighter_isGrounded = 1;
float leftFighter_moveSpeed = 9.0f;
PlayerKeybind leftFighter_keybind;
float leftFighter_currentFrameCounter = 0;

int leftFighter_ultimateGauge = 0;

// State timer
float leftFighter_stateTimer = 0.0f;
#define ATTACK_STATE_TIMEOUT 0.5f // 0.5 seconds for an attack state


// Combo system
#define MAX_COMBO_LENGTH 4
#define COMBO_TIMEOUT 2.0f

SDL_Scancode leftFighter_comboBuffer[MAX_COMBO_LENGTH];
int leftFighter_comboCount = 0;
float leftFighter_comboTimer = 0.0f;

void reset_combo() {
    leftFighter_comboCount = 0;
    leftFighter_comboTimer = 0.0f;
    for(int i = 0; i < MAX_COMBO_LENGTH; i++) {
        leftFighter_comboBuffer[i] = SDL_SCANCODE_UNKNOWN;
    }
}

void add_to_combo(SDL_Scancode input) {
    if(leftFighter_comboCount < MAX_COMBO_LENGTH) {
        leftFighter_comboBuffer[leftFighter_comboCount] = input;
        leftFighter_comboCount++;
        leftFighter_comboTimer = 0.0f; // Reset timer when new input added
    }
}

int check_combo_pattern(SDL_Scancode p1, SDL_Scancode p2, SDL_Scancode p3, SDL_Scancode p4) {
    if(leftFighter_comboCount != 4) return 0;
    return (leftFighter_comboBuffer[0] == p1 && 
            leftFighter_comboBuffer[1] == p2 && 
            leftFighter_comboBuffer[2] == p3 && 
            leftFighter_comboBuffer[3] == p4);
}

int check_and_execute_skill() {
    // TODO: Implement actual skill combos for leftFighter
    // Example: Skill 3: Light, Heavy, Light, Heavy
    // if(check_combo_pattern(leftFighter_keybind._light_punch, leftFighter_keybind._heavy_punch,
    //                        leftFighter_keybind._light_punch, leftFighter_keybind._heavy_punch)) {
    //     leftFighter_currentState = STATE_SKILL3;
    //     reset_combo();
    //     return 1;
    // }
    return 0;
}

void leftFighter_set_current_animation_state(int newAnimIndex) {
    if (leftFighter_currentAnimIndex != newAnimIndex) {
        leftFighter_currentAnimIndex = newAnimIndex;
        reset_animation_frame(leftFighter_anim, newAnimIndex + leftFighter_facingRight);
        leftFighter_currentFrameCounter = 0; // Reset frame counter when animation changes
    }
}

int get_anim_index_from_state(CharacterState state) {
    switch (state) {
        case STATE_IDLE: return idle;
        case STATE_WALK: return walk;
        case STATE_JUMP: return jump;
        case STATE_CROUCH: return crouch;
        case STATE_BLOCK_STAND: return block_stand;
        case STATE_BLOCK_CROUCH: return block_crouch;
        case STATE_LIGHT_PUNCH: return light1; // Assuming light1 for generic light punch
        case STATE_HEAVY_PUNCH: return heavy1; // Assuming heavy1 for generic heavy punch
        case STATE_LOW_PUNCH: return crouch_light1; // Assuming crouch_light1 for low punch
        case STATE_SKILL1: return skill1;
        case STATE_SKILL2: return skill2;
        case STATE_SKILL3: return skill3;
        case STATE_ULTIMATE: return ultimate;
        default: return idle; // Fallback to idle
    }
}

void leftFighter_start(){
    reset_combo();
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
    leftFighter_anim = flukeAnim; // Assuming flukeAnim is initialized elsewhere (e.g., menuscene)
    leftFighter_currentState = STATE_JUMP;
    // leftFighter_set_current_animation_state(idle);
}

void leftFighter_poll(SDL_Event* event){
    if(event->type == SDL_EVENT_KEY_DOWN){
        // กระโดด (W หรือ ลูกศรขึ้น)
        if((event->key.scancode == leftFighter_keybind._jump) && leftFighter_isGrounded){
            leftFighter_currentState = STATE_JUMP;
            leftFighter_velocityY = leftFighter_jumpForce;
            leftFighter_isGrounded = 0;
            add_to_combo(leftFighter_keybind._jump);
        }
        
        // ต่อยเบา (J หรือ 2) - ยืนเท่านั้น
        if(event->key.scancode == leftFighter_keybind._light_punch){
            if(leftFighter_currentState != STATE_LIGHT_PUNCH && 
               leftFighter_currentState != STATE_HEAVY_PUNCH &&
               leftFighter_currentState != STATE_LOW_PUNCH &&
               leftFighter_currentState != STATE_SKILL1 &&
               leftFighter_currentState != STATE_SKILL2 &&
               leftFighter_currentState != STATE_SKILL3 &&
               leftFighter_currentState != STATE_ULTIMATE &&
               leftFighter_currentState != STATE_CROUCH &&
               leftFighter_currentState != STATE_BLOCK_CROUCH){
                
                // Add to combo
                add_to_combo(leftFighter_keybind._light_punch);
                
                // Check if we can execute a skill
                if(!check_and_execute_skill()) {
                    // Normal light punch
                    leftFighter_currentState = STATE_LIGHT_PUNCH;
                }                
            }
        }
        
        // ต่อยหนัก (K หรือ 3) - ยืนเท่านั้น
        if(event->key.scancode == leftFighter_keybind._heavy_punch){
            if(leftFighter_currentState != STATE_LIGHT_PUNCH && 
               leftFighter_currentState != STATE_HEAVY_PUNCH &&
               leftFighter_currentState != STATE_LOW_PUNCH &&
               leftFighter_currentState != STATE_SKILL1 &&
               leftFighter_currentState != STATE_SKILL2 &&
               leftFighter_currentState != STATE_SKILL3 &&
               leftFighter_currentState != STATE_ULTIMATE &&
               leftFighter_currentState != STATE_CROUCH &&
               leftFighter_currentState != STATE_BLOCK_CROUCH){
                
                // Add to combo
                add_to_combo(leftFighter_keybind._heavy_punch);
                
                // Check if we can execute a skill
                if(!check_and_execute_skill()) {
                    // Normal heavy punch
                    leftFighter_currentState = STATE_HEAVY_PUNCH;
                }                
            }
        }
        
        // Ultimate (I หรือ 5) - ไม่สามารถบล็อกได้
        if(leftFighter_ultimateGauge >= 100 && event->key.scancode == leftFighter_keybind._ultimate){
            if(leftFighter_currentState != STATE_LIGHT_PUNCH && 
               leftFighter_currentState != STATE_HEAVY_PUNCH &&
               leftFighter_currentState != STATE_LOW_PUNCH &&
               leftFighter_currentState != STATE_SKILL1 &&
               leftFighter_currentState != STATE_SKILL2 &&
               leftFighter_currentState != STATE_SKILL3 &&
               leftFighter_currentState != STATE_ULTIMATE &&
               leftFighter_currentState != STATE_CROUCH &&
               leftFighter_currentState != STATE_BLOCK_CROUCH &&
               leftFighter_currentState != STATE_BLOCK_STAND){
                
                leftFighter_currentState = STATE_ULTIMATE;
                // printf("ULTIMATE ACTIVATED!\n");
            }
        }
    }
}

void leftFighter_loop(){
    float delta = get_delta();
    
    // Update combo timer
    if(leftFighter_comboCount > 0) {
        leftFighter_comboTimer += delta;
        if(leftFighter_comboTimer >= COMBO_TIMEOUT) {
            // printf("Combo timeout! Resetting...\n");
            reset_combo();
        }
    }

    // Handle state timer for attacks
    if (leftFighter_currentState == STATE_LIGHT_PUNCH ||
        leftFighter_currentState == STATE_HEAVY_PUNCH ||
        leftFighter_currentState == STATE_LOW_PUNCH) {
        leftFighter_stateTimer += delta;
        if (leftFighter_stateTimer >= ATTACK_STATE_TIMEOUT) {
            leftFighter_currentState = STATE_IDLE;
            leftFighter_stateTimer = 0.0f;
        }
    } else {
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
       leftFighter_currentState != STATE_LOW_PUNCH &&
       leftFighter_currentState != STATE_SKILL1 &&
       leftFighter_currentState != STATE_SKILL2 &&
       leftFighter_currentState != STATE_SKILL3 &&
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
                leftFighter_currentState = STATE_LOW_PUNCH;
            }
        }
        // เดินซ้าย (A หรือ ลูกศรซ้าย)
        else if((keyState[leftFighter_keybind._left]) && !isCrouching){
            leftFighter->x -= leftFighter_moveSpeed * delta;
            leftFighter_facingRight = 0;
            if(leftFighter_isGrounded && leftFighter_currentState != STATE_CROUCH){
                leftFighter_currentState = STATE_WALK;
            }
            moving = 1;
        }
        // เดินขวา (D หรือ ลูกศรขวา)
        else if((keyState[leftFighter_keybind._right]) && !isCrouching){
            leftFighter->x += leftFighter_moveSpeed * delta;
            leftFighter_facingRight = 1;
            if(leftFighter_isGrounded && leftFighter_currentState != STATE_CROUCH){
                leftFighter_currentState = STATE_WALK;
            }
            moving = 1;
        }
        // ถ้าไม่กดปุ่มใดๆ และอยู่บนพื้น ให้ idle
        else if(!moving && leftFighter_isGrounded && leftFighter_currentState != STATE_JUMP){
            leftFighter_currentState = STATE_IDLE;
        }
    }
    
    // จัดการแรงโน้มถ่วงและการกระโดด
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
    leftFighter_set_current_animation_state(get_anim_index_from_state(leftFighter_currentState));

    // Play the current animation
    if (leftFighter_anim != NULL) {
        play_animation(leftFighter, leftFighter_anim, &leftFighter_currentFrameCounter, leftFighter_currentAnimIndex, leftFighter_facingRight);
    }
}

void leftFighter_render(SDL_Renderer* renderer){
    render_entity(leftFighter, renderer, NULL);
}

void leftFighter_destroy(){
    destroy_entity(leftFighter);
}