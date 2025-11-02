#include "leftnamedisplay.h"
#include "../../entity.h"
#include <SDL3/SDL.h>
#include <stdio.h>
#include "../mainmenu/menustate.h"
#include "p1select.h"

// Forward declarations for entity lifecycle functions
void leftnamedisplay_start();
void leftnamedisplay_poll(SDL_Event* event);
void leftnamedisplay_loop();
void leftnamedisplay_render(SDL_Renderer* renderer);
void leftnamedisplay_destroy();

// Global entity pointer
Entity* leftnamedisplay = NULL;
int leftnamedisplay_previous = 0;

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
    set_text(leftnamedisplay, "Nerd");
    set_text_color(leftnamedisplay, 255, 255, 255, 255);
}

void leftnamedisplay_poll(SDL_Event* event) {
    // Handle events if needed
}

void leftnamedisplay_loop() {
    if(p1select_selectedIndex != leftnamedisplay_previous){
        const char* name_to_set;
        switch(p1select_selectedIndex) {
            case 0: name_to_set = "Nerd"; break; // Fluke
            case 1: name_to_set = "Crybaby"; break; // Bas
            case 2: name_to_set = "Drunken Homeless"; break; // Asia
            case 3: name_to_set = "Chuunibyou"; break; // Golf
            default: name_to_set = ""; break;
        }
        // The original code was using allFighters from menuscene which is FighterAnim*.
        // The fighter data with names is initialized in ithallscene.
        // To avoid complex changes, I'll just use the names you provided.
        // If you want to use the names from the Fighter struct, you need to initialize them in menuscene.
        set_text(leftnamedisplay, name_to_set);
        leftnamedisplay_previous = p1select_selectedIndex;
    }
    // Update logic per frame if needed
}

void leftnamedisplay_render(SDL_Renderer* renderer) {
    if(*menustate_state == 1)
    render_entity(leftnamedisplay, renderer, NULL);
}

void leftnamedisplay_destroy() {
    destroy_entity(leftnamedisplay);
}
