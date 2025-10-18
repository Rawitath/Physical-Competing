#include "animation.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL3/SDL_filesystem.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

Animation* create_animation(const char* animDir, float fps){
    Animation* anim = malloc(sizeof(Animation));
    anim->fps = fps;

    int count;
    char** imagePaths = SDL_GlobDirectory(animDir, "*.png", NULL, &count);
    
    SDL_Surface* mainSurface = IMG_Load(strcat(strcat(animDir, "/"), *(imagePaths)));

    int sizeX = mainSurface->w;
    int sizeY = mainSurface->h;
    
    for(int i = 1; i < count; i++){
        SDL_Surface* secondSurface = IMG_Load(strcat(strcat(animDir, "/"), *(imagePaths + i)));
        SDL_Rect dRect;
        dRect.x = sizeX * i + sizeX / 2;
        dRect.y = sizeY / 2;
        dRect.w = sizeX;
        dRect.h = sizeY;
        SDL_BlitSurface(secondSurface, NULL, mainSurface, &dRect);
    }

    anim->surface = mainSurface;

    return anim;
}
int destroy_animation(Animation* anim){
    free(anim);
    return 0;
}