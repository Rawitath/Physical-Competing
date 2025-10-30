// #include <SDL3/SDL.h>
// #include "../entity.h"
// #include "fluke.h"
// #include "../timesystem.h"
// #include "../scene.h"
// #include "../scenecontroller.h"
// #include <stdio.h>
// #include "../animation.h"
// #include "characterstate.h"
// #include "playerinput.h"

// void fluke_start();
// void fluke_poll(SDL_Event* event);
// void fluke_loop();
// void fluke_render(SDL_Renderer* renderer);
// void fluke_destroy();

// void fluke_init(){
//     fluke = create_entity(
//             NULL,
//             &fluke_start,
//             &fluke_poll,
//             &fluke_loop,
//             &fluke_render,
//             &fluke_destroy
//         );
// }


// CharacterState fluke_currentState = STATE_IDLE;
// int fluke_facingRight = 0; // 0 = left, 1 = right
// float fluke_velocityY = 0;
// float fluke_gravity = 80.0f;
// float fluke_jumpForce = 30.0f;
// int fluke_isGrounded = 1;
// float fluke_moveSpeed = 20.0f;

// Animation* currentAnim = NULL;

// // Combo system
// #define MAX_COMBO_LENGTH 4
// #define COMBO_TIMEOUT 2.0f

// PlayerInput comboBuffer[MAX_COMBO_LENGTH];
// int comboCount = 0;
// float comboTimer = 0.0f;

// void reset_combo() {
//     comboCount = 0;
//     comboTimer = 0.0f;
//     for(int i = 0; i < MAX_COMBO_LENGTH; i++) {
//         comboBuffer[i] = INPUT_NONE;
//     }
// }

// void add_to_combo(PlayerInput input) {
//     if(comboCount < MAX_COMBO_LENGTH) {
//         comboBuffer[comboCount] = input;
//         comboCount++;
//         comboTimer = 0.0f;
//     }
// }

// int check_combo_pattern(PlayerInput p1, PlayerInput p2, PlayerInput p3, PlayerInput p4) {
//     if(comboCount != 4) return 0;
//     return (comboBuffer[0] == p1 && 
//             comboBuffer[1] == p2 && 
//             comboBuffer[2] == p3 && 
//             comboBuffer[3] == p4);
// }

// int check_and_execute_skill() {
//     // TODO: เพิ่มคอมโบสำหรับ fluke ที่นี่
//     // Skill 1: ???
    
//     // Skill 2: ???
    
//     // Skill 3: ???
    
//     return 0;
// }

// void fluke_start(){
//     // currentAnim = idleLeft;
//     // set_image(fluke, currentAnim->paths[currentAnim->currentFrame]);
//     reset_combo();
// }

// void fluke_poll(SDL_Event* event){
//     if(event->type == SDL_EVENT_KEY_DOWN){
//         if((event->key.scancode == SDL_SCANCODE_W || 
//             event->key.scancode == SDL_SCANCODE_UP) && fluke_isGrounded){
//             currentState = STATE_JUMP;
//             velocityY = jumpForce;
//             isGrounded = 0;
//         }
        
//         if(event->key.scancode == SDL_SCANCODE_J || 
//            event->key.scancode == SDL_SCANCODE_2){
//             if(currentState != STATE_LIGHT_PUNCH && 
//                currentState != STATE_HEAVY_PUNCH &&
//                currentState != STATE_LOW_PUNCH &&
//                currentState != STATE_SKILL1 &&
//                currentState != STATE_SKILL2 &&
//                currentState != STATE_SKILL3 &&
//                currentState != STATE_ULTIMATE &&
//                currentState != STATE_CROUCH &&
//                currentState != STATE_BLOCK_CROUCH){
                
//                 add_to_combo(INPUT_LIGHT);
                
//                 if(!check_and_execute_skill()) {
//                     currentState = STATE_LIGHT_PUNCH;
//                     if(facingRight){
//                         set_animation(lightPunchRight);
//                     } else {
//                         set_animation(lightPunchLeft);
//                     }
//                 }
                
//                 printf("Combo: ");
//                 for(int i = 0; i < comboCount; i++) {
//                     printf("%d ", comboBuffer[i]);
//                 }
//                 printf("\n");
//             }
//         }
        
//         if(event->key.scancode == SDL_SCANCODE_K || 
//            event->key.scancode == SDL_SCANCODE_3){
//             if(currentState != STATE_LIGHT_PUNCH && 
//                currentState != STATE_HEAVY_PUNCH &&
//                currentState != STATE_LOW_PUNCH &&
//                currentState != STATE_SKILL1 &&
//                currentState != STATE_SKILL2 &&
//                currentState != STATE_SKILL3 &&
//                currentState != STATE_ULTIMATE &&
//                currentState != STATE_CROUCH &&
//                currentState != STATE_BLOCK_CROUCH){
                
//                 add_to_combo(INPUT_HEAVY);
                
//                 if(!check_and_execute_skill()) {
//                     currentState = STATE_HEAVY_PUNCH;
//                     if(facingRight){
//                         set_animation(heavyPunchRight);
//                     } else {
//                         set_animation(heavyPunchLeft);
//                     }
//                 }
                
//                 printf("Combo: ");
//                 for(int i = 0; i < comboCount; i++) {
//                     printf("%d ", comboBuffer[i]);
//                 }
//                 printf("\n");
//             }
//         }
        
//         if(event->key.scancode == SDL_SCANCODE_I || 
//            event->key.scancode == SDL_SCANCODE_5){
//             if(currentState != STATE_LIGHT_PUNCH && 
//                currentState != STATE_HEAVY_PUNCH &&
//                currentState != STATE_LOW_PUNCH &&
//                currentState != STATE_SKILL1 &&
//                currentState != STATE_SKILL2 &&
//                currentState != STATE_SKILL3 &&
//                currentState != STATE_ULTIMATE &&
//                currentState != STATE_CROUCH &&
//                currentState != STATE_BLOCK_CROUCH &&
//                currentState != STATE_BLOCK_STAND){
                
//                 currentState = STATE_ULTIMATE;
//                 if(facingRight){
//                     set_animation(ultimateRight);
//                 } else {
//                     set_animation(ultimateLeft);
//                 }
//                 printf("ULTIMATE ACTIVATED!\n");
//             }
//         }
//     }
// }

// float animTimer = 0;

// void fluke_loop(){
//     float delta = get_delta();
    
//     if(comboCount > 0) {
//         comboTimer += delta;
//         if(comboTimer >= COMBO_TIMEOUT) {
//             printf("Combo timeout! Resetting...\n");
//             reset_combo();
//         }
//     }
    
//     if(animTimer < 1.0f / currentAnim->fps){
//         animTimer += delta;
//     } else {
//         if(currentAnim->currentFrame < currentAnim->imageCount - 1){
//             currentAnim->currentFrame++;
//         } else {
//             currentAnim->currentFrame = 0;
            
//             if(currentState == STATE_LIGHT_PUNCH || 
//                currentState == STATE_HEAVY_PUNCH ||
//                currentState == STATE_SKILL1 ||
//                currentState == STATE_SKILL2 ||
//                currentState == STATE_SKILL3 ||
//                currentState == STATE_ULTIMATE){
//                 currentState = STATE_IDLE;
//             }
//             if(currentState == STATE_LOW_PUNCH){
//                 currentState = STATE_CROUCH;
//             }
//         }
//         set_image(fluke, currentAnim->paths[currentAnim->currentFrame]);
//         animTimer = 0;
//     }
    
//     const bool* keyState = SDL_GetKeyboardState(NULL);
    
//     int isBlocking = keyState[SDL_SCANCODE_L] || keyState[SDL_SCANCODE_1];
//     int isCrouching = keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_DOWN];
    
//     if(currentState != STATE_LIGHT_PUNCH && 
//        currentState != STATE_HEAVY_PUNCH && 
//        currentState != STATE_LOW_PUNCH &&
//        currentState != STATE_SKILL1 &&
//        currentState != STATE_SKILL2 &&
//        currentState != STATE_SKILL3 &&
//        currentState != STATE_ULTIMATE){
        
//         int moving = 0;
        
//         if(isBlocking && isCrouching && isGrounded){
//             currentState = STATE_BLOCK_CROUCH;
//             if(facingRight){
//                 set_animation(blockCrouchRight);
//             } else {
//                 set_animation(blockCrouchLeft);
//             }
//         }
//         else if(isBlocking && isGrounded && currentState != STATE_JUMP){
//             currentState = STATE_BLOCK_STAND;
//             if(facingRight){
//                 set_animation(blockStandRight);
//             } else {
//                 set_animation(blockStandLeft);
//             }
//         }
//         else if(isCrouching && isGrounded){
//             currentState = STATE_CROUCH;
//             if(facingRight){
//                 set_animation(crouchRight);
//             } else {
//                 set_animation(crouchLeft);
//             }
            
//             if(keyState[SDL_SCANCODE_J] || keyState[SDL_SCANCODE_2]){
//                 currentState = STATE_LOW_PUNCH;
//                 if(facingRight){
//                     set_animation(lowPunchRight);
//                 } else {
//                     set_animation(lowPunchLeft);
//                 }
//             }
//         }
//         else if((keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_LEFT]) && !isCrouching){
//             fluke->x -= moveSpeed * delta;
//             facingRight = 0;
//             if(isGrounded && currentState != STATE_CROUCH){
//                 currentState = STATE_WALK;
//                 set_animation(walkLeft);
//             }
//             moving = 1;
//         }
//         else if((keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_RIGHT]) && !isCrouching){
//             fluke->x += moveSpeed * delta;
//             facingRight = 1;
//             if(isGrounded && currentState != STATE_CROUCH){
//                 currentState = STATE_WALK;
//                 set_animation(walkRight);
//             }
//             moving = 1;
//         }
//         else if(!moving && isGrounded && currentState != STATE_JUMP){
//             currentState = STATE_IDLE;
//             if(facingRight){
//                 set_animation(idleRight);
//             } else {
//                 set_animation(idleLeft);
//             }
//         }
//     }
    
//     if(!isGrounded){
//         velocityY -= gravity * delta;
//         fluke->y += velocityY * delta;
        
//         if(facingRight){
//             set_animation(jumpRight);
//         } else {
//             set_animation(jumpLeft);
//         }
        
//         if(fluke->y <= 0){
//             fluke->y = 0;
//             velocityY = 0;
//             isGrounded = 1;
//             currentState = STATE_IDLE;
//         }
//     }
// }

// void fluke_render(SDL_Renderer* renderer){
//     render_entity(fluke, renderer, NULL);
// }

// void fluke_destroy(){
//     destroy_animation(idleLeft);
//     destroy_animation(idleRight);
//     destroy_animation(walkLeft);
//     destroy_animation(walkRight);
//     destroy_animation(crouchLeft);
//     destroy_animation(crouchRight);
//     destroy_animation(jumpLeft);
//     destroy_animation(jumpRight);
//     destroy_animation(lightPunchLeft);
//     destroy_animation(lightPunchRight);
//     destroy_animation(heavyPunchLeft);
//     destroy_animation(heavyPunchRight);
//     destroy_animation(blockStandLeft);
//     destroy_animation(blockStandRight);
//     destroy_animation(blockCrouchLeft);
//     destroy_animation(blockCrouchRight);
//     destroy_animation(lowPunchLeft);
//     destroy_animation(lowPunchRight);
//     destroy_animation(skill1Left);
//     destroy_animation(skill1Right);
//     destroy_animation(skill2Left);
//     destroy_animation(skill2Right);
//     destroy_animation(skill3Left);
//     destroy_animation(skill3Right);
//     destroy_animation(ultimateLeft);
//     destroy_animation(ultimateRight);
//     destroy_entity(fluke);
// }