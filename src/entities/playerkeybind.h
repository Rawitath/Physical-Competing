typedef enum SDL_Scancode SDL_Scancode;

typedef struct PlayerKeybind{
    SDL_Scancode _left;
    SDL_Scancode _right;
    SDL_Scancode _light_punch;
    SDL_Scancode _heavy_punch;
    SDL_Scancode _ultimate;
    SDL_Scancode _block;
    SDL_Scancode _jump;
    SDL_Scancode _crouch;
} PlayerKeybind;