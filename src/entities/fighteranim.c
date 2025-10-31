#include "fighteranim.h"
#include "../animation.h"
#include "../timesystem.h"
#include "../entity.h"
#include <stdlib.h>
#include <stdio.h>

FighterAnim *create_fighteranim()
{
    FighterAnim* a = (FighterAnim*) malloc(sizeof(FighterAnim));
    for(int i = 0; i < sizeof(a->anims) / sizeof(a->anims[0]); i++){ // Use sizeof to get array size
        a->anims[i] = NULL;
    }
    return a;
}

void destroy_fighteranim(FighterAnim *a)
{
    for(int i = 0; i < sizeof(a->anims) / sizeof(a->anims[0]); i++){ // Use sizeof to get array size
        if(a->anims[i] != NULL) free(a->anims[i]);
    }
    free(a);
}

void assign_anim(FighterAnim* a, int index, Animation *animation)
{
    a->anims[index] = animation;
}

void play_start_stop(Entity* entity, FighterAnim* a, float* framecounter, int index, int side, int start, int stop){
    if(a->anims[index + side]->imageCount < 1){
        return;
    }
    if(a->anims[index + side]->currentFrame < start) a->anims[index + side]->currentFrame = start;
    if(a->anims[index + side]->currentFrame >= stop) return;
    if(*framecounter < 1 / a->anims[index + side]->fps){
        *framecounter += get_delta();
    }
    else{
        while(*framecounter > 0){
            a->anims[index + side]->currentFrame += 1 + a->anims[index + side]->frameSkip;
            if(a->anims[index + side]->currentFrame >= a->anims[index + side]->imageCount - 1){
                a->anims[index + side]->currentFrame = 0;
            }
            *framecounter -= 1 / a->anims[index + side]->fps;
        }
        set_image(entity, a->anims[index + side]->paths[a->anims[index + side]->currentFrame]);
    }
}

void play_animation(Entity* entity, FighterAnim* a, float* framecounter, int index, int side)
{
    if(a->anims[index + side]->imageCount < 1){
        return;
    }
    if(*framecounter < 1 / a->anims[index + side]->fps){
        *framecounter += get_delta();
    }
    else{
        while(*framecounter > 0){
            a->anims[index + side]->currentFrame += 1 + a->anims[index + side]->frameSkip;
            if(a->anims[index + side]->currentFrame >= a->anims[index + side]->imageCount - 1){
                a->anims[index + side]->currentFrame = 0;
            }
            *framecounter -= 1 / a->anims[index + side]->fps;
        }
        set_image(entity, a->anims[index + side]->paths[a->anims[index + side]->currentFrame]);
    }
}

void play_animation_once(Entity* entity, FighterAnim* a, float* framecounter, int index, int side, int start, int stop, void (*on_complete)(void))
{
    Animation* anim = a->anims[index + side];
    if (anim->imageCount < 1) {
        if (on_complete) on_complete();
        return;
    }

    // If the animation is already past its end point, just call on_complete
    if (anim->currentFrame >= stop) {
        if (on_complete) on_complete();
        return;
    }

    *framecounter += get_delta();
    if (*framecounter >= 1.0f / anim->fps) {
        while (*framecounter >= 1.0f / anim->fps) {
            anim->currentFrame += 1 + anim->frameSkip;
            *framecounter -= 1.0f / anim->fps;
            if (anim->currentFrame >= stop) {
                anim->currentFrame = stop - 1; // Clamp to last frame
                set_image(entity, anim->paths[anim->currentFrame]);
                if (on_complete) on_complete();
                return;
            }
        }
        set_image(entity, anim->paths[anim->currentFrame]);
    }
}

void reset_animation_frame(FighterAnim* a, int index){
    if(a == NULL) return;
    if(a->anims[index] == NULL) return;
    a->anims[index]->currentFrame = 0;
}
