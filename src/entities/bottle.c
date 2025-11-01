#include "../entity.h"
#include "bottle.h"
#include <SDL3/SDL.h>
#include "../timesystem.h"

// Forward declarations for entity functions
void bottle_start();
void bottle_poll(SDL_Event* event);
void bottle_loop();
void bottle_render(SDL_Renderer* renderer);
void bottle_destroy();

// Global entity pointer
Entity* bottle;
float bottle_speed = 30;
int bottle_direction = 1; // 1 for right, 0 for left

void bottle_init() {
    // Assuming a path for the image, you can change "res/props/bottle.png" to the correct one.
    bottle = create_entity(
        "res/props/bottle.png",
        &bottle_start,
        &bottle_poll,
        &bottle_loop,
        &bottle_render,
        &bottle_destroy
    );
}

void release_bottle(float x, float y, int direction)
{
    bottle->x = x;
    bottle->y = y;
    bottle_direction = direction;
}

void bottle_start() {
    // Initialization logic on scene start
}

void bottle_poll(SDL_Event* event) {
    // Event handling logic for the bottle
}

void bottle_loop() {
    // Per-frame update logic for the bottle
    if(bottle_direction == 1){
        bottle->x += bottle_speed * get_delta();
    }
    else{
        bottle->x -= bottle_speed * get_delta();
    }
}

void bottle_render(SDL_Renderer* renderer) {
    render_entity(bottle, renderer, NULL);
}

void bottle_destroy() {
    destroy_entity(bottle);
}