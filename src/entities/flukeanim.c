#include "flukeAnim.h"
#include "fighteranim.h"
#include "../animation.h"

void flukeAnim_init()
{
    float fps = 15;
    flukeAnim = create_fighteranim();
    
    flukeAnim->anims[idle] = create_animation("res/fighters/fluke/idle_left", fps);
    flukeAnim->anims[idle + 1] = create_animation("res/fighters/fluke/idle_right", fps);
    flukeAnim->anims[walk] = create_animation("res/fighters/fluke/walk_left", fps);
    flukeAnim->anims[walk + 1] = create_animation("res/fighters/fluke/walk_right", fps);
    flukeAnim->anims[jump] = create_animation("res/fighters/fluke/jump_left", fps);
    flukeAnim->anims[jump + 1] = create_animation("res/fighters/fluke/jump_right", fps);
    flukeAnim->anims[crouch] = create_animation("res/fighters/fluke/crouch_left", fps);
    flukeAnim->anims[crouch + 1] = create_animation("res/fighters/fluke/crouch_right", fps);
    flukeAnim->anims[crouching] = create_animation("res/fighters/fluke/crouching_left", fps);
    flukeAnim->anims[crouching + 1] = create_animation("res/fighters/fluke/crouching_right", fps);
    flukeAnim->anims[light1] = create_animation("res/fighters/fluke/light1_left", fps);
    flukeAnim->anims[light1 + 1] = create_animation("res/fighters/fluke/light1_right", fps);
    flukeAnim->anims[light2] = create_animation("res/fighters/fluke/light2_left", fps);
    flukeAnim->anims[light2 + 1] = create_animation("res/fighters/fluke/light2_right", fps);
    flukeAnim->anims[light3] = create_animation("res/fighters/fluke/light3_left", fps);
    flukeAnim->anims[light3 + 1] = create_animation("res/fighters/fluke/light3_right", fps);
    flukeAnim->anims[heavy1] = create_animation("res/fighters/fluke/heavy1_left", fps);
    flukeAnim->anims[heavy1 + 1] = create_animation("res/fighters/fluke/heavy1_right", fps);
    flukeAnim->anims[heavy2] = create_animation("res/fighters/fluke/heavy2_left", fps);
    flukeAnim->anims[heavy2 + 1] = create_animation("res/fighters/fluke/heavy2_right", fps);
    flukeAnim->anims[heavy3] = create_animation("res/fighters/fluke/heavy3_left", fps);
    flukeAnim->anims[heavy3 + 1] = create_animation("res/fighters/fluke/heavy3_right", fps);
    flukeAnim->anims[crouch_light1] = create_animation("res/fighters/fluke/crouch_light1_left", fps);
    flukeAnim->anims[crouch_light1 + 1] = create_animation("res/fighters/fluke/crouch_light1_right", fps);
    flukeAnim->anims[crouch_light2] = create_animation("res/fighters/fluke/crouch_light2_left", fps);
    flukeAnim->anims[crouch_light2 + 1] = create_animation("res/fighters/fluke/crouch_light2_right", fps);
    flukeAnim->anims[crouch_light3] = create_animation("res/fighters/fluke/crouch_light3_left", fps);
    flukeAnim->anims[crouch_light3 + 1] = create_animation("res/fighters/fluke/crouch_light3_right", fps);
    flukeAnim->anims[crouch_heavy1] = create_animation("res/fighters/fluke/crouch_heavy1_left", fps);
    flukeAnim->anims[crouch_heavy1 + 1] = create_animation("res/fighters/fluke/crouch_heavy1_right", fps);
    flukeAnim->anims[crouch_heavy2] = create_animation("res/fighters/fluke/crouch_heavy2_left", fps);
    flukeAnim->anims[crouch_heavy2 + 1] = create_animation("res/fighters/fluke/crouch_heavy2_right", fps);
    flukeAnim->anims[crouch_heavy3] = create_animation("res/fighters/fluke/crouch_heavy3_left", fps);
    flukeAnim->anims[crouch_heavy3 + 1] = create_animation("res/fighters/fluke/crouch_heavy3_right", fps);
    flukeAnim->anims[skill1] = create_animation("res/fighters/fluke/skill1_left", fps);
    flukeAnim->anims[skill1 + 1] = create_animation("res/fighters/fluke/skill1_right", fps);
    flukeAnim->anims[skill2] = create_animation("res/fighters/fluke/skill2_left", fps);
    flukeAnim->anims[skill2 + 1] = create_animation("res/fighters/fluke/skill2_right", fps);
    flukeAnim->anims[skill3] = create_animation("res/fighters/fluke/skill3_left", fps);
    flukeAnim->anims[skill3 + 1] = create_animation("res/fighters/fluke/skill3_right", fps);
    flukeAnim->anims[ultimate] = create_animation("res/fighters/fluke/ultimate_left", fps);
    flukeAnim->anims[ultimate + 1] = create_animation("res/fighters/fluke/ultimate_right", fps);
    flukeAnim->anims[damaged] = create_animation("res/fighters/fluke/damaged_left", fps);
    flukeAnim->anims[damaged + 1] = create_animation("res/fighters/fluke/damaged_right", fps);
    flukeAnim->anims[startle] = create_animation("res/fighters/fluke/startle_left", fps);
    flukeAnim->anims[startle + 1] = create_animation("res/fighters/fluke/startle_right", fps);
    flukeAnim->anims[fall] = create_animation("res/fighters/fluke/fall_left", fps);
    flukeAnim->anims[fall + 1] = create_animation("res/fighters/fluke/fall_right", fps);
    flukeAnim->anims[win] = create_animation("res/fighters/fluke/win_left", fps);
    flukeAnim->anims[win + 1] = create_animation("res/fighters/fluke/win_right", fps);
}
