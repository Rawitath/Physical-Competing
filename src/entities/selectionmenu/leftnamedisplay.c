#include "leftnamedisplay.h"
#include "../../entity.h"
#include <SDL3/SDL.h>
#include <stdio.h>

// Forward declarations for entity lifecycle functions
void leftnamedisplay_start();
void leftnamedisplay_poll(SDL_Event* event);
void leftnamedisplay_loop();
void leftnamedisplay_render(SDL_Renderer* renderer);
void leftnamedisplay_destroy();

// Global entity pointer
Entity* leftnamedisplay = NULL;

/**
 * @brief Initializes the left name display UI text entity.
 */
void leftnamedisplay_init() {
    leftnamedisplay = ui_create_text(
        "res/Bangers-Regular.ttf", // Default font
        48,                             // Default font size
        &leftnamedisplay_start,
        &leftnamedisplay_poll,
        &leftnamedisplay_loop,
        &leftnamedisplay_render,
        &leftnamedisplay_destroy
    );
}

/**
 * @brief Start function for the left name display entity.
 * Called once when the entity is added to a scene.
 */
void leftnamedisplay_start() {
    leftnamedisplay->x = 15;
    leftnamedisplay->y = 8;
    set_text(leftnamedisplay, "Player 1");
    set_text_color(leftnamedisplay, 0, 0, 0, 255);
}

void leftnamedisplay_poll(SDL_Event* event) {
    // Handle events if needed
}

void leftnamedisplay_loop() {
    // Update logic per frame if needed
}

void leftnamedisplay_render(SDL_Renderer* renderer) {
    render_entity(leftnamedisplay, renderer, NULL);
}

void leftnamedisplay_destroy() {
    destroy_entity(leftnamedisplay);
}

