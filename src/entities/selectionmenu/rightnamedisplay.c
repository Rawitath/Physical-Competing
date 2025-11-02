#include "rightnamedisplay.h"
#include "../../entity.h"
#include <SDL3/SDL.h>
#include <stdio.h>

// Forward declarations for entity lifecycle functions
void rightnamedisplay_start();
void rightnamedisplay_poll(SDL_Event* event);
void rightnamedisplay_loop();
void rightnamedisplay_render(SDL_Renderer* renderer);
void rightnamedisplay_destroy();

// Global entity pointer
Entity* rightnamedisplay = NULL;

/**
 * @brief Initializes the left name display UI text entity.
 */
void rightnamedisplay_init() {
    rightnamedisplay = ui_create_text(
        "res/Bangers-Regular.ttf", // Default font
        48,                             // Default font size
        &rightnamedisplay_start,
        &rightnamedisplay_poll,
        &rightnamedisplay_loop,
        &rightnamedisplay_render,
        &rightnamedisplay_destroy
    );
}

/**
 * @brief Start function for the left name display entity.
 * Called once when the entity is added to a scene.
 */
void rightnamedisplay_start() {
    rightnamedisplay->x = 85;
    rightnamedisplay->y = 8;
    set_text(rightnamedisplay, "Player 1");
    set_text_color(rightnamedisplay, 0, 0, 0, 255);
}

void rightnamedisplay_poll(SDL_Event* event) {
    // Handle events if needed
}

void rightnamedisplay_loop() {
    // Update logic per frame if needed
}

void rightnamedisplay_render(SDL_Renderer* renderer) {
    render_entity(rightnamedisplay, renderer, NULL);
}

void rightnamedisplay_destroy() {
    destroy_entity(rightnamedisplay);
}

