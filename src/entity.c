#include "entity.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string.h>
#include <stdio.h>

Entity *create_entity(const char* imgPath, void (*start)(), void (*poll)(SDL_Event *event), void (*loop)(), void (*render)(SDL_Renderer *renderer), void (*destroy)())
{
    Entity* entity = (Entity*) malloc(sizeof(Entity));
    entity->x = 0.0;
    entity->y = 0.0;
    entity->w = 1.0;
    entity->h = 1.0;
    entity->start = start;
    entity->poll = poll;
    entity->loop = loop;
    entity->render = render;
    entity->destroy = destroy;

    entity->scene = NULL;

    if(imgPath != NULL){
        entity->surface = IMG_Load(imgPath);
    }
    return entity;
}

int render_entity(Entity *entity, SDL_Renderer *renderer)
{
    if(entity->surface == NULL){
        return RENDER_SURFACE_NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, entity->surface);

    SDL_FRect fRect;
    fRect.x = entity->x;
    fRect.y = entity->y;
    fRect.w = entity->surface->w * entity->w;
    fRect.h = entity->surface->h * entity->h;
    SDL_RenderTexture(renderer, texture, NULL, &fRect);
    SDL_DestroyTexture(texture);
    return RENDER_SUCCESS;
}

void destroy_entity(Entity* entity){
    SDL_DestroySurface(entity->surface);
    free(entity);
}
