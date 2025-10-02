#include "entity.h"
#include "scene.h"

#include <string.h>
#include <stdio.h>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

Entity *create_entity(const char* imgPath, void (*start)(), void (*poll)(SDL_Event *event), void (*loop)(), void (*render)(SDL_Renderer *renderer), void (*destroy)())
{
    Entity* entity = (Entity*) malloc(sizeof(Entity));
    entity->x = 0.0;
    entity->y = 0.0;
    entity->w = 1.0;
    entity->h = 1.0;
    entity->anchorX = 0.0;
    entity->anchorY = 0.0;

    entity->pixelRatio = 0.01;

    entity->start = start;
    entity->poll = poll;
    entity->loop = loop;
    entity->render = render;
    entity->destroy = destroy;

    entity->scene = NULL;

    entity->imgSizeX = 1;
    entity->imgSizeY = 1;

    if(imgPath != NULL){
        entity->surface = IMG_Load(imgPath);
        if(entity->surface != NULL){
            entity->imgSizeX = entity->surface->w;
            entity->imgSizeY = entity->surface->h;
        }
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

    int offsetX;
    int offsetY;

    SDL_GetCurrentRenderOutputSize(renderer, &offsetX, &offsetY);

    offsetX = offsetX / 2 - entity->scene->viewportX * entity->scene->viewportZoom;
    offsetY = offsetY / 2 - entity->scene->viewportY * entity->scene->viewportZoom;

    float sizeW = entity->imgSizeX * entity->w * entity->scene->viewportZoom;
    float sizeH = entity->imgSizeY * entity->h * entity->scene->viewportZoom;

    fRect.x = (entity->x + entity->anchorX) * entity->scene->viewportZoom + offsetX - sizeW / 2;
    fRect.y = (-entity->y + entity->anchorY) * entity->scene->viewportZoom + offsetY - sizeH / 2;
    fRect.w = sizeW;
    fRect.h = sizeH;

    SDL_RenderTexture(renderer, texture, NULL, &fRect);
    SDL_DestroyTexture(texture);
    return RENDER_SUCCESS;
}

void destroy_entity(Entity* entity){
    SDL_DestroySurface(entity->surface);
    free(entity);
}
