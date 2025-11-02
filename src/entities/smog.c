#include "../entity.h"
#include "smog.h"
#include <SDL3/SDL.h>
#include "../timesystem.h"
#include "../scene.h"
#include "leftFighter.h"
#include "rightFighter.h"
#include "../scene.h"
#include "roundsystem.h"

// Forward declarations for entity functions
void smog_start();
void smog_poll(SDL_Event* event);
void smog_loop();
void smog_render(SDL_Renderer* renderer);
void smog_destroy();

// Global entity pointer
Entity* smog;

// Smog properties
float smog_duration = 13.0f; // How long the smog lasts in seconds
float smog_pre = 6.0f;
float smog_timer = 0.0f;

// Damage over time properties
const float SMOG_DAMAGE_COOLDOWN = 0.5f; // Time between damage ticks
const int SMOG_DAMAGE = 2;               // Damage per tick
float smog_left_fighter_damage_timer = 0.0f;
float smog_right_fighter_damage_timer = 0.0f;

void smog_init() {
    // Create the smog entity, assuming a placeholder image path.
    // You should replace "res/props/smog.png" with your actual smog image.
    smog = create_entity(
        "res/props/smog.png",
        &smog_start,
        &smog_poll,
        &smog_loop,
        &smog_render,
        &smog_destroy
    );
}


void release_smog(Entity* fighter)
{
    smog_timer = 0;
    smog_left_fighter_damage_timer = SMOG_DAMAGE_COOLDOWN; // Ready to damage immediately
    smog_right_fighter_damage_timer = SMOG_DAMAGE_COOLDOWN;

    // Position the smog at the fighter's feet
    smog->x = fighter->x;
    smog->y = fighter->y;
}

void smog_start() {
    // Adjust size if needed
    smog->img->imgSizeX *= 6;
    smog->img->imgSizeY *= 4;
}

void smog_poll(SDL_Event* event) {
    // Smog doesn't need to handle events
}

// AABB collision check //keep as relic
// int smog_check_collision(Entity* a, Entity* b) {
//     if (!a || !b || !a->active || !b->active) {
//         return 0;
//     }
//     return fabsf(a->x - b->x) < (a->w + b->w) / 2 &&
//            fabsf(a->y - b->y) < (a->h + b->h) / 2;
// }

void smog_loop() {
    if (!smog) return;

    float delta = get_delta();
    smog_timer += delta;

    if(smog_timer < smog_pre) return;
    // Check if the smog's duration has expired
    if (smog_timer >= smog_duration) {
        remove_entity(smog->scene, smog);
        smog->destroy();
        smog = NULL;
        return;
    }

    // Update damage timers
    smog_left_fighter_damage_timer += delta;
    smog_right_fighter_damage_timer += delta;

    // Check for collision with left fighter and deal damage over time
    if (rs_leftfighter != 3) {//golf 
        if (smog_left_fighter_damage_timer >= SMOG_DAMAGE_COOLDOWN) {
            leftFighter_subtract_health(SMOG_DAMAGE);
            smog_left_fighter_damage_timer = 0.0f; // Reset timer
        }
    }

    // Check for collision with right fighter and deal damage over time
    if (rs_rightfighter != 3) {//golf
        if (smog_right_fighter_damage_timer >= SMOG_DAMAGE_COOLDOWN) {
            rightFighter_subtract_health(SMOG_DAMAGE);
            smog_right_fighter_damage_timer = 0.0f; // Reset timer
        }
    }
}

void smog_render(SDL_Renderer* renderer) {
    if(smog_timer < smog_pre) return;
    SDL_SetSurfaceAlphaMod(smog->img->surface, 80);
    render_entity(smog, renderer, NULL);
}

void smog_destroy() {
    destroy_entity(smog);
}