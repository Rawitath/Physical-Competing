#include "../entity.h"
#include "jobpaper.h"
#include <SDL3/SDL.h>
#include "../timesystem.h"
#include "../scene.h"
#include "leftFighter.h"
#include "rightFighter.h"

// Forward declarations for entity functions
void jobpaper_start();
void jobpaper_poll(SDL_Event* event);
void jobpaper_loop();
void jobpaper_render(SDL_Renderer* renderer);
void jobpaper_destroy();

// Global entity pointer
Entity* jobpaper;
float jobpaper_speed = 14;
int jobpaper_direction = 1; // 1 for right, 0 for left
float jobpaper_duration = 5;
float jobpaper_timer = 0;
float jobpaper_remX = 0;

void jobpaper_init() {
    // Assuming a path for the image, you can change "res/props/jobpaper.png" to the correct one.
    jobpaper = create_entity(
        "res/props/jobpaper.png",
        &jobpaper_start,
        &jobpaper_poll,
        &jobpaper_loop,
        &jobpaper_render,
        &jobpaper_destroy
    );
}

void release_jobpaper(Entity* fighter, int direction)
{
    jobpaper_timer = 0;
    jobpaper->x = fighter->x;
    jobpaper->y = fighter->y;
    jobpaper_remX = fighter->x;

    jobpaper_direction = direction;
}

void jobpaper_start() {
    jobpaper->img->imgSizeX *= 0.3;
    jobpaper->img->imgSizeY *= 0.3;
    // Initialization logic on scene start
}

void jobpaper_poll(SDL_Event* event) {
    // Event handling logic for the jobpaper
}

// AABB 
int jobpaper_check_collision(Entity* a, Entity* b) {
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

void jobpaper_loop() {
    if (!jobpaper) return;
    // Per-frame update logic for the jobpaper
    jobpaper_timer += get_delta();
    if (jobpaper_timer < jobpaper_duration) {
        if(jobpaper_direction == 1){
        jobpaper->x += jobpaper_speed * get_delta();
        }
        else{
            jobpaper->x -= jobpaper_speed * get_delta();
        }
    }
    else {
        remove_entity(jobpaper->scene, jobpaper);
        jobpaper->destroy();
        jobpaper = NULL;
        return;
    }

    // Check for collision with fighters
    if (jobpaper_check_collision(jobpaper, leftFighter)) {
        leftFighter_subtract_health(10); // Deal 10 damage
        remove_entity(jobpaper->scene, jobpaper);
        jobpaper->destroy();
        jobpaper = NULL;
    } else if (jobpaper_check_collision(jobpaper, rightFighter)) {
        rightFighter_subtract_health(10); // Deal 10 damage
        remove_entity(jobpaper->scene, jobpaper);
        jobpaper->destroy();
        jobpaper = NULL;
    }

}

void jobpaper_render(SDL_Renderer* renderer) {
    render_entity(jobpaper, renderer, NULL);
}

void jobpaper_destroy() {
    destroy_entity(jobpaper);
}
