#include "golfanim.h"
#include "fighteranim.h"
#include "../animation.h"

void golfAnim_init()
{
    float fps = 15;
    golfAnim = create_fighteranim();
    
    golfAnim->anims[idle] = create_animation("res/fighters/golf/idle_left", fps);
    golfAnim->anims[idle + 1] = create_animation("res/fighters/golf/idle_right", fps);
    golfAnim->anims[walk] = create_animation("res/fighters/golf/walk_left", fps);
    golfAnim->anims[walk + 1] = create_animation("res/fighters/golf/walk_right", fps);
    golfAnim->anims[jump] = create_animation("res/fighters/golf/jump_left", fps);
    golfAnim->anims[jump + 1] = create_animation("res/fighters/golf/jump_right", fps);
    golfAnim->anims[crouch] = create_animation("res/fighters/golf/crouch_left", fps);
    golfAnim->anims[crouch + 1] = create_animation("res/fighters/golf/crouch_right", fps);
    golfAnim->anims[crouching] = create_animation("res/fighters/golf/crouching_left", fps);
    golfAnim->anims[crouching + 1] = create_animation("res/fighters/golf/crouching_right", fps);
    golfAnim->anims[light1] = create_animation("res/fighters/golf/light1_left", fps);
    golfAnim->anims[light1 + 1] = create_animation("res/fighters/golf/light1_right", fps);
    golfAnim->anims[light2] = create_animation("res/fighters/golf/light2_left", fps);
    golfAnim->anims[light2 + 1] = create_animation("res/fighters/golf/light2_right", fps);
    golfAnim->anims[light3] = create_animation("res/fighters/golf/light3_left", fps);
    golfAnim->anims[light3 + 1] = create_animation("res/fighters/golf/light3_right", fps);
    golfAnim->anims[heavy1] = create_animation("res/fighters/golf/heavy1_left", fps);
    golfAnim->anims[heavy1 + 1] = create_animation("res/fighters/golf/heavy1_right", fps);
    golfAnim->anims[heavy2] = create_animation("res/fighters/golf/heavy2_left", fps);
    golfAnim->anims[heavy2 + 1] = create_animation("res/fighters/golf/heavy2_right", fps);
    golfAnim->anims[heavy3] = create_animation("res/fighters/golf/heavy3_left", fps);
    golfAnim->anims[heavy3 + 1] = create_animation("res/fighters/golf/heavy3_right", fps);
    golfAnim->anims[crouch_light1] = create_animation("res/fighters/golf/crouch_light1_left", fps);
    golfAnim->anims[crouch_light1 + 1] = create_animation("res/fighters/golf/crouch_light1_right", fps);
    golfAnim->anims[crouch_light2] = create_animation("res/fighters/golf/crouch_light2_left", fps);
    golfAnim->anims[crouch_light2 + 1] = create_animation("res/fighters/golf/crouch_light2_right", fps);
    golfAnim->anims[crouch_light3] = create_animation("res/fighters/golf/crouch_light3_left", fps);
    golfAnim->anims[crouch_light3 + 1] = create_animation("res/fighters/golf/crouch_light3_right", fps);
    golfAnim->anims[crouch_heavy1] = create_animation("res/fighters/golf/crouch_heavy1_left", fps);
    golfAnim->anims[crouch_heavy1 + 1] = create_animation("res/fighters/golf/crouch_heavy1_right", fps);
    golfAnim->anims[crouch_heavy2] = create_animation("res/fighters/golf/crouch_heavy2_left", fps);
    golfAnim->anims[crouch_heavy2 + 1] = create_animation("res/fighters/golf/crouch_heavy2_right", fps);
    golfAnim->anims[crouch_heavy3] = create_animation("res/fighters/golf/crouch_heavy3_left", fps);
    golfAnim->anims[crouch_heavy3 + 1] = create_animation("res/fighters/golf/crouch_heavy3_right", fps);
    golfAnim->anims[skill1] = create_animation("res/fighters/golf/skill1_left", fps);
    golfAnim->anims[skill1 + 1] = create_animation("res/fighters/golf/skill1_right", fps);
    golfAnim->anims[skill2] = create_animation("res/fighters/golf/skill2_left", fps);
    golfAnim->anims[skill2 + 1] = create_animation("res/fighters/golf/skill2_right", fps);
    golfAnim->anims[skill3] = create_animation("res/fighters/golf/skill3_left", fps);
    golfAnim->anims[skill3 + 1] = create_animation("res/fighters/golf/skill3_right", fps);
    golfAnim->anims[ultimate] = create_animation("res/fighters/golf/ultimate_left", fps);
    golfAnim->anims[ultimate + 1] = create_animation("res/fighters/golf/ultimate_right", fps);
    golfAnim->anims[damaged] = create_animation("res/fighters/golf/damaged_left", fps);
    golfAnim->anims[damaged + 1] = create_animation("res/fighters/golf/damaged_right", fps);
    golfAnim->anims[startle] = create_animation("res/fighters/golf/startle_left", fps);
    golfAnim->anims[startle + 1] = create_animation("res/fighters/golf/startle_right", fps);
    golfAnim->anims[fall] = create_animation("res/fighters/golf/fall_left", fps);
    golfAnim->anims[fall + 1] = create_animation("res/fighters/golf/fall_right", fps);
    golfAnim->anims[win] = create_animation("res/fighters/golf/win_left", fps);
    golfAnim->anims[win + 1] = create_animation("res/fighters/golf/win_right", fps);
    // Add block animations
    golfAnim->anims[block_stand] = create_animation("res/fighters/golf/block_stand_left", fps);
    golfAnim->anims[block_stand + 1] = create_animation("res/fighters/golf/block_stand_right", fps);
    golfAnim->anims[block_crouch] = create_animation("res/fighters/golf/block_crouch_left", fps);
    golfAnim->anims[block_crouch + 1] = create_animation("res/fighters/golf/block_crouch_right", fps);

    for(int i = 0; i < sizeof(golfAnim->anims) / sizeof(golfAnim->anims[0]); i++){
        if(!golfAnim->anims[i]){
            continue;
        }
        for(int j = 0; j < golfAnim->anims[i]->imageCount; j++){
            if(i == idle || i == idle + 1){
                golfAnim->anims[i]->offsets[j].x = 0;
            golfAnim->anims[i]->offsets[j].y = -2.7;
            golfAnim->anims[i]->offsets[j].w = 0.75;
            golfAnim->anims[i]->offsets[j].h = 0.75;
            }
            else{
                golfAnim->anims[i]->offsets[j].x = 0;
            golfAnim->anims[i]->offsets[j].y = -2.7;
            golfAnim->anims[i]->offsets[j].w = 0.95;
            golfAnim->anims[i]->offsets[j].h = 0.95;
            }
            
        }
        golfAnim->anims[i]->frameSkip = 1;
    }
}
