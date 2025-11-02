#include "rightnamedisplay.h"
#include "../../entity.h"
#include <SDL3/SDL.h>
#include <stdio.h>
#include "../mainmenu/menustate.h"
#include "p2select.h"
#include "../allfighterstruct.h"
#include "../fighterstruct.h"

// Forward declarations for entity lifecycle functions
void rightnamedisplay_start();
void rightnamedisplay_poll(SDL_Event* event);
void rightnamedisplay_loop();
void rightnamedisplay_render(SDL_Renderer* renderer);
void rightnamedisplay_destroy();

// Global entity pointer
Entity* rightnamedisplay = NULL;
int rightnamedisplay_previous = 0;

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
    set_text(rightnamedisplay, "Nerd");
    set_text_color(rightnamedisplay, 255, 255, 255, 255);
}

void rightnamedisplay_poll(SDL_Event* event) {
    // Handle events if needed
}

void rightnamedisplay_loop() {
    if(p2select_selectedIndex != rightnamedisplay_previous){
        const char* name_to_set;
        switch(p2select_selectedIndex) {
            case 0: name_to_set = "Nerd"; break; // Fluke
            case 1: name_to_set = "Crybaby"; break; // Bas
            case 2: name_to_set = "Drunken Homeless"; break; // Asia
            case 3: name_to_set = "Chuunibyou"; break; // Golf
            default: name_to_set = ""; break;
        }

        set_text(rightnamedisplay, name_to_set);
        rightnamedisplay_previous = p2select_selectedIndex;
    }
    // Update logic per frame if needed
}

void rightnamedisplay_render(SDL_Renderer* renderer) {
    if(*menustate_state == 1) render_entity(rightnamedisplay, renderer, NULL);
}

void rightnamedisplay_destroy() {
    destroy_entity(rightnamedisplay);
}
