#include "../entity.h"
#include "drill.h"
#include <SDL3/SDL.h>
#include "../timesystem.h"

// Forward declarations for entity functions
void drill_start();
void drill_poll(SDL_Event* event);
void drill_loop();
void drill_render(SDL_Renderer* renderer);
void drill_destroy();

// Global entity pointer
Entity* drill;
float drill_speed = 7;
int drill_direction = 1; // 1 for right, 0 for left

void drill_init() {
    // Assuming a path for the image, you can change "res/props/drill.png" to the correct one.
    drill = create_entity(
        "res/props/drill.png",
        &drill_start,
        &drill_poll,
        &drill_loop,
        &drill_render,
        &drill_destroy
    );
}

void release_drill(float x, float y, int direction)
{
    drill->x = x;
    drill->y = y;
    drill_direction = direction;
}

void drill_start() {
    // Initialization logic on scene start
}

void drill_poll(SDL_Event* event) {
    // Event handling logic for the drill
}

void drill_loop() {
    // Per-frame update logic for the drill
    if(drill_direction == 1){
        drill->x += drill_speed * get_delta();
    }
    else{
        drill->x -= drill_speed * get_delta();
    }
}

void drill_render(SDL_Renderer* renderer) {
    render_entity(drill, renderer, NULL);
}

void drill_destroy() {
    destroy_entity(drill);
}