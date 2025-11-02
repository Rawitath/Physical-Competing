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
    anim->currentFrame = 0;
    anim->frameSkip = 0;

    int count;
    char** imagePaths = SDL_GlobDirectory(animDir, "*.png", 0, &count);
    anim->imageCount = count;

    anim->paths = (const char**)malloc(count * sizeof(const char*));
    anim->offsets = (AnimOffset*) malloc(count * sizeof(AnimOffset));

    // --- FIX IS HERE ---
    for(int i = 0; i < count; i++){
        char* fileName = imagePaths[i];
        
        // Calculate the exact length needed: "dir" + "/" + "file.png" + "\0"
        unsigned long long len = strlen(animDir) + 1 + strlen(fileName) + 1;
        
        // Allocate memory for the final, full path
        char* fullPath = malloc(len);
        
        if (fullPath) {
            // Safely build the path string
            snprintf(fullPath, len, "%s/%s", animDir, fileName);
            anim->paths[i] = fullPath; // Assign the newly allocated string
        } else {
            // Handle malloc failure if necessary
            anim->paths[i] = NULL; 
        }
        anim->offsets[i].index = i;
        anim->offsets[i].x = 0;
        anim->offsets[i].y = 0;
        anim->offsets[i].w = 1;
        anim->offsets[i].h = 1;
    }

    return anim;
}
int destroy_animation(Animation* anim){
    if(anim == NULL){
        return 0;
    }
    for(int i = 0; i < anim->imageCount; i++){
        free(*(anim->paths + i));
    }
    free(anim->offsets);
    free(anim->paths);
    free(anim);
    return 0;
}