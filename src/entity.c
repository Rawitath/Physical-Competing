#include "entity.h"
#include <SDL3/SDL.h>

int render_sprite(Sprite* sprite, SDL_Renderer* renderer){
    if(sprite->surface == NULL){
        return RENDER_SURFACE_NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, sprite->surface);

    SDL_FRect fRect;
    fRect.x = sprite->entity.x;
    fRect.y = sprite->entity.y;
    fRect.w = sprite->entity.w;
    fRect.h = sprite->entity.h;
    SDL_RenderTexture(renderer, texture, NULL, &fRect);
    SDL_DestroyTexture(texture);
    return RENDER_SUCCESS;
}

void destroy_sprite(Sprite *sprite){
    SDL_DestroySurface(sprite->surface);
    free(sprite);
}
