#include "fighteranim.h"
#include "../animation.h"
#include "../timesystem.h"
#include "../entity.h"
#include <stdlib.h>
#include <stdio.h>

FighterAnim *create_fighteranim()
{
    FighterAnim* a = (FighterAnim*) malloc(sizeof(FighterAnim));
    for(int i = 0; i < 50; i++){
        a->anims[i] = NULL;
    }
    return a;
}

void destroy_fighteranim(FighterAnim *a)
{
    for(int i = 0; i < 50; i++){
        if(a->anims[i] != NULL) free(a->anims[i]);
    }
    free(a);
}

void assign_anim(FighterAnim* a, int index, Animation *animation)
{
    a->anims[index] = animation;
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
