#include "fightcontroller.h"
#include "../entity.h"
#include <SDL3/SDL.h>
#include "leftFighter.h"

// Forward declarations for entity functions
void fightcontroller_start();
void fightcontroller_poll(SDL_Event* event);
void fightcontroller_loop();
void fightcontroller_render(SDL_Renderer* renderer);
void fightcontroller_destroy();

// Global entity pointer
Entity* fightcontroller;

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
}

void fightcontroller_poll(SDL_Event* event) {
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
    // Per-frame update logic for fight control
}

void fightcontroller_render(SDL_Renderer* renderer) {
    // This is a controller entity, so it likely won't render anything.
}

void fightcontroller_destroy() {
    destroy_entity(fightcontroller);
}