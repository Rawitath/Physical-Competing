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

    int count;
    char** imagePaths = SDL_GlobDirectory(animDir, "*.png", NULL, &count);
    anim->imageCount = count;

    anim->paths = (const char**)malloc(count * sizeof(const char*));
    anim->offsets = (AnimOffset*) malloc(count * sizeof(AnimOffset));

    // for(int i = 0; i < count; i++){
    //     char* fileName = imagePaths[i];
    //     char* path = strdup(animDir);
    //     realloc(path)
    //     strcat(path, "/");
    //     strcat(path, fileName);
    //     anim->paths[i] = strdup(path);
    // }

    // --- FIX IS HERE ---
    for(int i = 0; i < count; i++){
        char* fileName = imagePaths[i];
        
        // Calculate the exact length needed: "dir" + "/" + "file.png" + "\0"
        size_t len = strlen(animDir) + 1 + strlen(fileName) + 1;
        
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