#include "basAnim.h"
#include "fighteranim.h"
#include "../animation.h"

void basAnim_init()
{
    float fps = 15;
    basAnim = create_fighteranim();
    
    basAnim->anims[idle] = create_animation("res/fighters/bas/idle_left", fps);
    basAnim->anims[idle + 1] = create_animation("res/fighters/bas/idle_right", fps);
    basAnim->anims[walk] = create_animation("res/fighters/bas/walk_left", fps);
    basAnim->anims[walk + 1] = create_animation("res/fighters/bas/walk_right", fps);
    basAnim->anims[jump] = create_animation("res/fighters/bas/jump_left", fps);
    basAnim->anims[jump + 1] = create_animation("res/fighters/bas/jump_right", fps);
    basAnim->anims[crouch] = create_animation("res/fighters/bas/crouching_left", fps);
    basAnim->anims[crouch + 1] = create_animation("res/fighters/bas/crouching_right", fps);
    basAnim->anims[crouching] = create_animation("res/fighters/bas/crouch_left", fps);
    basAnim->anims[crouching + 1] = create_animation("res/fighters/bas/crouch_right", fps);
    basAnim->anims[light1] = create_animation("res/fighters/bas/light1_left", fps);
    basAnim->anims[light1 + 1] = create_animation("res/fighters/bas/light1_right", fps);
    basAnim->anims[light2] = create_animation("res/fighters/bas/light2_left", fps);
    basAnim->anims[light2 + 1] = create_animation("res/fighters/bas/light2_right", fps);
    basAnim->anims[light3] = create_animation("res/fighters/bas/light3_left", fps);
    basAnim->anims[light3 + 1] = create_animation("res/fighters/bas/light3_right", fps);
    basAnim->anims[heavy1] = create_animation("res/fighters/bas/heavy1_left", fps);
    basAnim->anims[heavy1 + 1] = create_animation("res/fighters/bas/heavy1_right", fps);
    basAnim->anims[heavy2] = create_animation("res/fighters/bas/heavy2_left", fps);
    basAnim->anims[heavy2 + 1] = create_animation("res/fighters/bas/heavy2_right", fps);
    basAnim->anims[heavy3] = create_animation("res/fighters/bas/heavy3_left", fps);
    basAnim->anims[heavy3 + 1] = create_animation("res/fighters/bas/heavy3_right", fps);
    basAnim->anims[crouch_light1] = create_animation("res/fighters/bas/crouch_light1_left", fps);
    basAnim->anims[crouch_light1 + 1] = create_animation("res/fighters/bas/crouch_light1_right", fps);
    basAnim->anims[crouch_light2] = create_animation("res/fighters/bas/crouch_light2_left", fps);
    basAnim->anims[crouch_light2 + 1] = create_animation("res/fighters/bas/crouch_light2_right", fps);
    basAnim->anims[crouch_light3] = create_animation("res/fighters/bas/crouch_light3_left", fps);
    basAnim->anims[crouch_light3 + 1] = create_animation("res/fighters/bas/crouch_light3_right", fps);
    basAnim->anims[crouch_heavy1] = create_animation("res/fighters/bas/crouch_heavy1_left", fps);
    basAnim->anims[crouch_heavy1 + 1] = create_animation("res/fighters/bas/crouch_heavy1_right", fps);
    basAnim->anims[crouch_heavy2] = create_animation("res/fighters/bas/crouch_heavy2_left", fps);
    basAnim->anims[crouch_heavy2 + 1] = create_animation("res/fighters/bas/crouch_heavy2_right", fps);
    basAnim->anims[crouch_heavy3] = create_animation("res/fighters/bas/crouch_heavy3_left", fps);
    basAnim->anims[crouch_heavy3 + 1] = create_animation("res/fighters/bas/crouch_heavy3_right", fps);
    basAnim->anims[skill1] = create_animation("res/fighters/bas/skill1_left", fps);
    basAnim->anims[skill1 + 1] = create_animation("res/fighters/bas/skill1_right", fps);
    basAnim->anims[skill2] = create_animation("res/fighters/bas/skill2_left", fps);
    basAnim->anims[skill2 + 1] = create_animation("res/fighters/bas/skill2_right", fps);
    basAnim->anims[skill3] = create_animation("res/fighters/bas/skill3_left", fps);
    basAnim->anims[skill3 + 1] = create_animation("res/fighters/bas/skill3_right", fps);
    basAnim->anims[ultimate] = create_animation("res/fighters/bas/ultimate_left", fps);
    basAnim->anims[ultimate + 1] = create_animation("res/fighters/bas/ultimate_right", fps);
    basAnim->anims[damaged] = create_animation("res/fighters/bas/damaged_left", fps);
    basAnim->anims[damaged + 1] = create_animation("res/fighters/bas/damaged_right", fps);
    basAnim->anims[startle] = create_animation("res/fighters/bas/startle_left", fps);
    basAnim->anims[startle + 1] = create_animation("res/fighters/bas/startle_right", fps);
    basAnim->anims[fall] = create_animation("res/fighters/bas/fall_left", fps);
    basAnim->anims[fall + 1] = create_animation("res/fighters/bas/fall_right", fps);
    basAnim->anims[win] = create_animation("res/fighters/bas/win_left", fps);
    basAnim->anims[win + 1] = create_animation("res/fighters/bas/win_right", fps);
    // Add block animations
    basAnim->anims[block_stand] = create_animation("res/fighters/bas/guard_left", fps * 2);
    basAnim->anims[block_stand + 1] = create_animation("res/fighters/bas/guard_right", fps * 2);
    basAnim->anims[block_crouch] = create_animation("res/fighters/bas/crouch_guard_left", fps * 2);
    basAnim->anims[block_crouch + 1] = create_animation("res/fighters/bas/crouch_guard_right", fps * 2);

    for(int i = 0; i < sizeof(basAnim->anims) / sizeof(basAnim->anims[0]); i++){ 
        if(!basAnim->anims[i]){
            continue;
        }
        for(int j = 0; j < basAnim->anims[i]->imageCount; j++){
            if(i == walk || i == walk + 1 || 
                i == crouch || i == crouch + 1 || 
                i == crouch_light1 || i == crouch_light1 + 1 ||
                 i == crouch_light2 || i == crouch_light2 + 1 ||
                 i == crouch_light3 || i == crouch_light3 + 1 ||
                  i == crouch_heavy1 || i == crouch_heavy1 + 1 ||
                  i == crouch_heavy2 || i == crouch_heavy2 + 1 ||
                   i == crouch_heavy3 || i == crouch_heavy3 + 1 ||
                 i == block_crouch || i == block_crouch + 1 ||
                i == jump || i == jump + 1){
                basAnim->anims[i]->offsets[j].x = 0;
                basAnim->anims[i]->offsets[j].y = -1;
                basAnim->anims[i]->offsets[j].w = 1.8;
                basAnim->anims[i]->offsets[j].h = 1.8;
                }
                else if(i == light1 || i == light1 + 1 || 
                i == light2 || i == light2 + 1 || 
                i == light3 || i == light3 + 1 ||
                 i == jump || i == jump + 1){
                    basAnim->anims[i]->offsets[j].x = 0;
                    basAnim->anims[i]->offsets[j].y = -1;
                    basAnim->anims[i]->offsets[j].w = 1.95;
                    basAnim->anims[i]->offsets[j].h = 1.95;
                }
            else{
                basAnim->anims[i]->offsets[j].x = 0;
                basAnim->anims[i]->offsets[j].y = -1;
                basAnim->anims[i]->offsets[j].w = 1.45;
                basAnim->anims[i]->offsets[j].h = 1.45;
                
            }
            
        }
    }
}
