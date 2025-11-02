#include "../entity.h"
#include "drill.h"
#include <SDL3/SDL.h>
#include "../timesystem.h"
#include "../scene.h"
#include "leftFighter.h"
#include "rightFighter.h"

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
float drill_duration = 5;
float drill_timer = 0;

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

void release_drill(Entity* fighter, int direction)
{
    drill_timer = 0;
    drill->x = fighter->x;
    drill->y = fighter->y;

    drill_direction = direction;
}

void drill_start() {
    drill->img->imgSizeX *= 0.6;
    drill->img->imgSizeY *= 0.6;
    // Initialization logic on scene start
}

void drill_poll(SDL_Event* event) {
    // Event handling logic for the drill
}

// AABB 
int drill_check_collision(Entity* a, Entity* b) {
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

void drill_loop() {
    if (!drill) return;

    // Per-frame update logic for the drill
    drill_timer += get_delta();
    if (drill_timer < drill_duration) {
        if(drill_direction == 1){
        drill->x += drill_speed * get_delta();
        }
        else{
            drill->x -= drill_speed * get_delta();
        }
    }
    else {
        remove_entity(drill->scene, drill);
        drill->destroy();
        drill = NULL;
        return;
    }

    // Check for collision with fighters
    if (drill_check_collision(drill, leftFighter)) {
        leftFighter_subtract_health(10); // Deal 10 damage
        remove_entity(drill->scene, drill);
        drill->destroy();
        drill = NULL;
    } else if (drill_check_collision(drill, rightFighter)) {
        rightFighter_subtract_health(10); // Deal 10 damage
        remove_entity(drill->scene, drill);
        drill->destroy();
        drill = NULL;
    }

}

void drill_render(SDL_Renderer* renderer) {
    render_entity(drill, renderer, NULL);
}

void drill_destroy() {
    destroy_entity(drill);
}