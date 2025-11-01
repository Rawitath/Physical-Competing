#include "../entity.h"
#include "bottle.h"
#include <SDL3/SDL.h>
#include "../timesystem.h"
#include "../scene.h"
#include "leftFighter.h"
#include "rightFighter.h"

// Forward declarations for entity functions
void bottle_start();
void bottle_poll(SDL_Event* event);
void bottle_loop();
void bottle_render(SDL_Renderer* renderer);
void bottle_destroy();

// Global entity pointer
Entity* bottle;
float bottle_speed = 5;
float bottle_velocityY = 0;
int bottle_direction = 1; // 1 for right, 0 for left
float bottle_duration = 5;
float bottle_timer = 0;


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

int bottle_check_collision(Entity* a, Entity* b) {
    if (!a || !b || !a->active || !b->active) {
        return 0;
    }

    // The sides of the rectangles
    float leftA, leftB;
    float rightA, rightB;
    float topA, topB;
    float bottomA, bottomB;

    // Calculate the sides of rect A
    leftA = a->x - (a->w * a->anchorX);
    rightA = a->x + (a->w * (1.0f - a->anchorX));
    topA = a->y + (a->h * (1.0f - a->anchorY));
    bottomA = a->y - (a->h * a->anchorY);

    // Calculate the sides of rect B
    leftB = b->x - (b->w * b->anchorX);
    rightB = b->x + (b->w * (1.0f - b->anchorX));
    topB = b->y + (b->h * (1.0f - b->anchorY));
    bottomB = b->y - (b->h * b->anchorY);

    // If any of the sides from A are outside of B
    if (bottomA >= topB) return 0;
    if (topA <= bottomB) return 0;
    if (rightA <= leftB) return 0;
    if (leftA >= rightB) return 0;

    // If none of the sides from A are outside B
    return 1;
}

void release_bottle(float x, float y, int direction)
{
    bottle_timer = 0.0;
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
    bottle_timer += get_delta();
    bottle->y += bottle_velocityY;
    bottle_velocityY -= 9.8 * get_delta();
    if(bottle_timer >= bottle_duration){
    if(bottle_direction == 1){
        bottle->x += bottle_speed * get_delta();
    }
    else{
        bottle->x -= bottle_speed * get_delta();
    }
}
    else {
        remove_entity(bottle->scene, bottle);
        bottle->destroy();
        bottle = NULL;
        return;
    }

    // Check for collision with fighters
    if (drill_check_collision(bottle, leftFighter)) {
        leftFighter_subtract_health(10); // Deal 10 damage
        remove_entity(bottle->scene, bottle);
        bottle->destroy();
        bottle = NULL;
    } else if (drill_check_collision(bottle, rightFighter)) {
        rightFighter_subtract_health(10); // Deal 10 damage
        remove_entity(bottle->scene, bottle);
        bottle->destroy();
        bottle = NULL;
    }
}

void bottle_render(SDL_Renderer* renderer) {
    render_entity(bottle, renderer, NULL);
}

void bottle_destroy() {
    destroy_entity(bottle);
}