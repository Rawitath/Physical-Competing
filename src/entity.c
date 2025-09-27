#include "entity.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

Entity *create_entity(void (*start)(), void (*poll)(SDL_Event *event), void (*loop)(), void (*render)(SDL_Renderer *renderer), void (*destroy)())
{
    Entity* entity = (Entity*) malloc(sizeof(Entity*));
    entity->x = 0.0;
    entity->y = 0.0;
    entity->w = 0.0;
    entity->h = 0.0;
    entity->start = start;
    entity->poll = poll;
    entity->loop = loop;
    entity->render = render;
    entity->destroy = destroy;

    entity->scene = NULL;

    return entity;
}

Sprite *create_sprite(const char *imgPath, Entity entity)
{
    Sprite* sprite = (Sprite*) malloc(sizeof(Sprite*));
    sprite->entity = entity;
    sprite->surface = IMG_Load(imgPath);
    return sprite;
}

int render_sprite(Sprite *sprite, SDL_Renderer *renderer)
{
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
void destroy_entity(Entity* entity){
    free(entity);
}
