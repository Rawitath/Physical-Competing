#include "entity.h"
#include "scene.h"
#include <stdlib.h>

#include <string.h>
#include <stdio.h>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

void img_allocon(Entity *entity, const char* imgPath){
    entity->img = (ImageContainer*) malloc(sizeof(ImageContainer));
    entity->img->pixelRatio = 0.01;
    entity->img->imgSizeX = 1;
    entity->img->imgSizeY = 1;

    entity->img->surface = IMG_Load(imgPath);
    if(entity->img->surface != NULL){
        entity->img->imgSizeX = entity->img->surface->w;
        entity->img->imgSizeY = entity->img->surface->h;
    }
}

void txt_allocon(Entity *entity, const char* fontPath, float size){
    entity->txt = (TextContainer*) malloc(sizeof(TextContainer));
    entity->txt->font = TTF_OpenFont(fontPath, size);
    entity->txt->horizontalAlign = 0;
    entity->txt->verticalAlign = 0;
    entity->txt->text = "Lorem Ipsum";
    entity->txt->r = 0;
    entity->txt->g = 0;
    entity->txt->b = 0;
    entity->txt->a = SDL_ALPHA_OPAQUE;
}

Entity *create_entity(const char* imgPath, void (*start)(), void (*poll)(SDL_Event *event), void (*loop)(), void (*render)(SDL_Renderer *renderer), void (*destroy)())
{
    Entity* entity = (Entity*) malloc(sizeof(Entity));

    entity->type = ENTITY_TYPE_SPRITE;
    entity->x = 0.0;
    entity->y = 0.0;
    entity->w = 1.0;
    entity->h = 1.0;
    entity->anchorX = 0.0;
    entity->anchorY = 0.0;
    entity->active = ACTIVE_TRUE;

    entity->needStart = 1;

    entity->start = start;
    entity->poll = poll;
    entity->loop = loop;
    entity->render = render;
    entity->destroy = destroy;

    entity->scene = NULL;

    img_allocon(entity, imgPath);

    return entity;
}

Entity *ui_create_text(const char* fontPath, float size, void (*start)(), void (*poll)(SDL_Event *event), void (*loop)(), void (*render)(SDL_Renderer *renderer), void (*destroy)())
{
    Entity* entity = (Entity*) malloc(sizeof(Entity));

    entity->type = ENTITY_TYPE_UITEXT;
    entity->x = 0.0;
    entity->y = 0.0;
    entity->w = 1.0;
    entity->h = 1.0;
    entity->anchorX = 0.0;
    entity->anchorY = 0.0;
    entity->active = ACTIVE_TRUE;

    entity->start = start;
    entity->poll = poll;
    entity->loop = loop;
    entity->render = render;
    entity->destroy = destroy;

    entity->scene = NULL;

    txt_allocon(entity, fontPath, size);

    return entity;
}

int render_image(Entity* entity, SDL_Renderer* renderer, SDL_FRect* sRect){
    if(entity->img->surface == NULL){
        return RENDER_SURFACE_NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, entity->img->surface);

    SDL_FRect fRect;

    int offsetX;
    int offsetY;

    SDL_GetCurrentRenderOutputSize(renderer, &offsetX, &offsetY);

    offsetX = offsetX / 2 - entity->scene->viewportX * entity->scene->viewportZoom;
    offsetY = offsetY / 2 - entity->scene->viewportY * entity->scene->viewportZoom;

    float sizeW = entity->img->imgSizeX * entity->w * entity->scene->viewportZoom * entity->img->pixelRatio;
    float sizeH = entity->img->imgSizeY * entity->h * entity->scene->viewportZoom * entity->img->pixelRatio;

    fRect.x = (entity->x + entity->anchorX) * entity->scene->viewportZoom + offsetX - sizeW / 2;
    fRect.y = (-entity->y + entity->anchorY) * entity->scene->viewportZoom + offsetY - sizeH / 2;
    fRect.w = sizeW;
    fRect.h = sizeH;

    SDL_RenderTexture(renderer, texture, sRect, &fRect);
    SDL_DestroyTexture(texture);
    return RENDER_SUCCESS;
}

int render_text(Entity* entity, SDL_Renderer* renderer, SDL_FRect* sRect){
    if(entity->txt->font == NULL){
        return RENDER_FONT_NULL;
    }
    SDL_Color color;
    color.r = entity->txt->r;
    color.g = entity->txt->g;
    color.b = entity->txt->b;
    color.a = entity->txt->a;
    SDL_Surface* surface = TTF_RenderText_Blended(entity->txt->font, entity->txt->text, 0, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    SDL_FRect fRect;

    int offsetX;
    int offsetY;

    SDL_GetCurrentRenderOutputSize(renderer, &offsetX, &offsetY);

    offsetX = offsetX / 2 - entity->scene->viewportX * entity->scene->viewportZoom;
    offsetY = offsetY / 2 - entity->scene->viewportY * entity->scene->viewportZoom;

    float sizeW;
    float sizeH;

    SDL_GetTextureSize(texture, &sizeW, &sizeH);

    sizeW = sizeW * entity->w * entity->scene->viewportZoom;
    sizeH = sizeH * entity->h * entity->scene->viewportZoom;

    fRect.x = (entity->x + entity->anchorX) * entity->scene->viewportZoom + offsetX - sizeW / 2;
    fRect.y = (-entity->y + entity->anchorY) * entity->scene->viewportZoom + offsetY - sizeH / 2;
    fRect.w = sizeW;
    fRect.h = sizeH;

    SDL_RenderTexture(renderer, texture, sRect, &fRect);

    SDL_DestroyTexture(texture);
    return RENDER_SUCCESS;
}

int ui_render_image(Entity* entity, SDL_Renderer* renderer, SDL_FRect* sRect){
    if(entity->img->surface == NULL){
        return RENDER_SURFACE_NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, entity->img->surface);

    SDL_FRect fRect;

    int offsetX;
    int offsetY;

    SDL_GetCurrentRenderOutputSize(renderer, &offsetX, &offsetY);

    float fOffsetX = (float)offsetX / UI_REFERENCE_X;
    float fOffsetY = (float)offsetY / UI_REFERENCE_Y;

    float sizeW = entity->img->imgSizeX * entity->img->pixelRatio * entity->w;
    float sizeH = entity->img->imgSizeY * entity->img->pixelRatio * entity->h;

    fRect.x = (entity->x + entity->anchorX) * fOffsetX - sizeW / 2;
    fRect.y = (entity->y + entity->anchorY) * fOffsetY - sizeH / 2;
    fRect.w = sizeW * fOffsetX;
    fRect.h = sizeH * fOffsetY;

    SDL_RenderTexture(renderer, texture, sRect, &fRect);
    SDL_DestroyTexture(texture);
    return RENDER_SUCCESS;
}


int ui_render_text(Entity* entity, SDL_Renderer* renderer, SDL_FRect* sRect){
    if(entity->txt->font == NULL){
        return RENDER_FONT_NULL;
    }
    SDL_Color color;
    color.r = entity->txt->r;
    color.g = entity->txt->g;
    color.b = entity->txt->b;
    color.a = entity->txt->a;
    SDL_Surface* surface = TTF_RenderText_Blended(entity->txt->font, entity->txt->text, 0, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    SDL_FRect fRect;

    int offsetX;
    int offsetY;

    SDL_GetCurrentRenderOutputSize(renderer, &offsetX, &offsetY);

    float fOffsetX = (float)offsetX / UI_REFERENCE_X;
    float fOffsetY = (float)offsetY / UI_REFERENCE_Y;

    float sizeW ;
    float sizeH;

    SDL_GetTextureSize(texture, &sizeW, &sizeH);

    sizeW = sizeW * entity->w;
    sizeH = sizeH * entity->h;

    fRect.x = (entity->x + entity->anchorX) * fOffsetX - sizeW / 2;
    fRect.y = (entity->y + entity->anchorY) * fOffsetY - sizeH / 2;
    fRect.w = sizeW;
    fRect.h = sizeH;

    SDL_RenderTexture(renderer, texture, sRect, &fRect);

    SDL_DestroyTexture(texture);
    return RENDER_SUCCESS;
}

int render_entity(Entity *entity, SDL_Renderer *renderer, SDL_FRect* sRect)
{
    switch (entity->type){
        case ENTITY_TYPE_SPRITE:
            return render_image(entity, renderer, sRect);
        case ENTITY_TYPE_TEXT:
            return render_text(entity, renderer, sRect);
        case ENTITY_TYPE_UIIMAGE:
            return ui_render_image(entity, renderer, sRect);
        case ENTITY_TYPE_UITEXT:
            return ui_render_text(entity, renderer, sRect);
    }
    return RENDER_UNKNOWN_TYPE;
}

void destroy_text(Entity *text)
{
    TTF_CloseFont(text->txt->font);
    free(text);
}

void destroy_image(Entity *entity){
    SDL_DestroySurface(entity->img->surface);
    free(entity);
}

void destroy_entity(Entity* entity){
    if(entity->type == ENTITY_TYPE_SPRITE || entity->type == ENTITY_TYPE_UIIMAGE){
        destroy_image(entity);
    }
    else if(entity->type == ENTITY_TYPE_TEXT || entity->type == ENTITY_TYPE_UITEXT){
        destroy_text(entity);
    }
}



int set_image(Entity* entity, const char* imgPath){
    if(entity->type != ENTITY_TYPE_SPRITE && entity->type != ENTITY_TYPE_UIIMAGE){
        return ENTITY_INVALID_TYPE;
    }
    SDL_DestroySurface(entity->img->surface);
    entity->img->surface = IMG_Load(imgPath);
    if(entity->img->surface != NULL){
        entity->img->imgSizeX = entity->img->surface->w;
        entity->img->imgSizeY = entity->img->surface->h;
    }
    return SET_SUCCESS;
}
int set_image_surface(Entity *entity, SDL_Surface *surface)
{
    if(entity->type != ENTITY_TYPE_SPRITE && entity->type != ENTITY_TYPE_UIIMAGE){
        return ENTITY_INVALID_TYPE;
    }
    entity->img->surface = surface;
    if(entity->img->surface != NULL){
        entity->img->imgSizeX = entity->img->surface->w;
        entity->img->imgSizeY = entity->img->surface->h;
    }
    return SET_SUCCESS;
}
int set_text(Entity *entity, const char *text)
{
    if(entity->type != ENTITY_TYPE_TEXT && entity->type != ENTITY_TYPE_UITEXT){
        return ENTITY_INVALID_TYPE;
    }
    strcpy(entity->txt->text, text);
    return SET_SUCCESS;
}
const char *get_text(Entity *entity)
{
    if(entity->type != ENTITY_TYPE_TEXT && entity->type != ENTITY_TYPE_UITEXT){
        return NULL;
    }
    return entity->txt->text;
}
int set_font(Entity *entity, const char *fontPath, float fontSize)
{
    if(entity->type != ENTITY_TYPE_TEXT && entity->type != ENTITY_TYPE_UITEXT){
        return ENTITY_INVALID_TYPE;
    }
    TTF_CloseFont(entity->txt->font);
    entity->txt->font = TTF_OpenFont(fontPath, fontSize);
    return SET_SUCCESS;
}

int set_font_size(Entity *entity, float fontSize)
{
    if(entity->type != ENTITY_TYPE_TEXT && entity->type != ENTITY_TYPE_UITEXT){
        return ENTITY_INVALID_TYPE;
    }
    if(!TTF_SetFontSize(entity->txt->font, fontSize)){
        return SET_FAILED;
    }
    return SET_SUCCESS;
}

float get_font_size(Entity *entity)
{
    if(entity->type != ENTITY_TYPE_TEXT && entity->type != ENTITY_TYPE_UITEXT){
        return ENTITY_INVALID_TYPE;
    }
    return TTF_GetFontSize(entity->txt->font);
}
