#include "asiaAnim.h"
#include "fighteranim.h"
#include "../animation.h"

void asiaAnim_init()
{
    float fps = 15;
    asiaAnim = create_fighteranim();
    
    asiaAnim->anims[idle] = create_animation("res/fighters/asia/idle_right", fps);
    asiaAnim->anims[idle + 1] = create_animation("res/fighters/asia/idle_left", fps);
    asiaAnim->anims[walk] = create_animation("res/fighters/asia/walk_right", fps);
    asiaAnim->anims[walk + 1] = create_animation("res/fighters/asia/walk_left", fps);
    asiaAnim->anims[jump] = create_animation("res/fighters/asia/jump_right", fps);
    asiaAnim->anims[jump + 1] = create_animation("res/fighters/asia/jump_left", fps);
    asiaAnim->anims[crouch] = create_animation("res/fighters/asia/crouching_right", fps);
    asiaAnim->anims[crouch + 1] = create_animation("res/fighters/asia/crouching_left", fps);
    asiaAnim->anims[crouching] = create_animation("res/fighters/asia/crouch_right", fps);
    asiaAnim->anims[crouching + 1] = create_animation("res/fighters/asia/crouch_left", fps);
    asiaAnim->anims[light1] = create_animation("res/fighters/asia/light1_right", fps);
    asiaAnim->anims[light1 + 1] = create_animation("res/fighters/asia/light1_left", fps);
    asiaAnim->anims[light2] = create_animation("res/fighters/asia/light2_right", fps);
    asiaAnim->anims[light2 + 1] = create_animation("res/fighters/asia/light2_left", fps);
    asiaAnim->anims[light3] = create_animation("res/fighters/asia/light3_right", fps);
    asiaAnim->anims[light3 + 1] = create_animation("res/fighters/asia/light3_left", fps);
    asiaAnim->anims[heavy1] = create_animation("res/fighters/asia/heavy1_right", fps);
    asiaAnim->anims[heavy1 + 1] = create_animation("res/fighters/asia/heavy1_left", fps);
    asiaAnim->anims[heavy2] = create_animation("res/fighters/asia/heavy2_right", fps);
    asiaAnim->anims[heavy2 + 1] = create_animation("res/fighters/asia/heavy2_left", fps);
    asiaAnim->anims[heavy3] = create_animation("res/fighters/asia/heavy3_right", fps);
    asiaAnim->anims[heavy3 + 1] = create_animation("res/fighters/asia/heavy3_left", fps);
    asiaAnim->anims[crouch_light1] = create_animation("res/fighters/asia/crouch_light1_right", fps);
    asiaAnim->anims[crouch_light1 + 1] = create_animation("res/fighters/asia/crouch_light1_left", fps);
    asiaAnim->anims[crouch_light2] = create_animation("res/fighters/asia/crouch_light2_right", fps);
    asiaAnim->anims[crouch_light2 + 1] = create_animation("res/fighters/asia/crouch_light2_left", fps);
    asiaAnim->anims[crouch_light3] = create_animation("res/fighters/asia/crouch_light3_right", fps);
    asiaAnim->anims[crouch_light3 + 1] = create_animation("res/fighters/asia/crouch_light3_left", fps);
    asiaAnim->anims[crouch_heavy1] = create_animation("res/fighters/asia/crouch_heavy1_right", fps);
    asiaAnim->anims[crouch_heavy1 + 1] = create_animation("res/fighters/asia/crouch_heavy1_left", fps);
    asiaAnim->anims[crouch_heavy2] = create_animation("res/fighters/asia/crouch_heavy2_right", fps);
    asiaAnim->anims[crouch_heavy2 + 1] = create_animation("res/fighters/asia/crouch_heavy2_left", fps);
    asiaAnim->anims[crouch_heavy3] = create_animation("res/fighters/asia/crouch_heavy3_right", fps);
    asiaAnim->anims[crouch_heavy3 + 1] = create_animation("res/fighters/asia/crouch_heavy3_left", fps);
    asiaAnim->anims[skill1] = create_animation("res/fighters/asia/skill1_right", fps);
    asiaAnim->anims[skill1 + 1] = create_animation("res/fighters/asia/skill1_left", fps);
    asiaAnim->anims[skill2] = create_animation("res/fighters/asia/skill2_right", fps);
    asiaAnim->anims[skill2 + 1] = create_animation("res/fighters/asia/skill2_left", fps);
    asiaAnim->anims[skill3] = create_animation("res/fighters/asia/skill3_right", fps);
    asiaAnim->anims[skill3 + 1] = create_animation("res/fighters/asia/skill3_left", fps);
    asiaAnim->anims[ultimate] = create_animation("res/fighters/asia/ultimate_right", fps);
    asiaAnim->anims[ultimate + 1] = create_animation("res/fighters/asia/ultimate_left", fps);
    asiaAnim->anims[damaged] = create_animation("res/fighters/asia/damaged_right", fps);
    asiaAnim->anims[damaged + 1] = create_animation("res/fighters/asia/damaged_left", fps);
    asiaAnim->anims[startle] = create_animation("res/fighters/asia/startle_right", fps);
    asiaAnim->anims[startle + 1] = create_animation("res/fighters/asia/startle_left", fps);
    asiaAnim->anims[fall] = create_animation("res/fighters/asia/fall_right", fps);
    asiaAnim->anims[fall + 1] = create_animation("res/fighters/asia/fall_left", fps);
    asiaAnim->anims[win] = create_animation("res/fighters/asia/win_right", fps);
    asiaAnim->anims[win + 1] = create_animation("res/fighters/asia/win_left", fps);
    // Add block animations
    asiaAnim->anims[block_stand] = create_animation("res/fighters/asia/guard_right", fps * 2);
    asiaAnim->anims[block_stand + 1] = create_animation("res/fighters/asia/guard_left", fps * 2);
    asiaAnim->anims[block_crouch] = create_animation("res/fighters/asia/crouch_guard_right", fps * 2);
    asiaAnim->anims[block_crouch + 1] = create_animation("res/fighters/asia/crouch_guard_left", fps * 2);

    for(int i = 0; i < sizeof(asiaAnim->anims) / sizeof(asiaAnim->anims[0]); i++){ 
        if(!asiaAnim->anims[i]){
            continue;
        }
        for(int j = 0; j < asiaAnim->anims[i]->imageCount; j++){
            asiaAnim->anims[i]->offsets[j].x = 0;
            asiaAnim->anims[i]->offsets[j].y = 0;
            asiaAnim->anims[i]->offsets[j].w = 1.15;
            asiaAnim->anims[i]->offsets[j].h = 1.15;
        }
    }
}
