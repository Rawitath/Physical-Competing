typedef struct Animation Animation;
typedef struct Entity Entity;

enum FighterAnimState {
    idle = 0,
    walk = 2,
    jump = 4,
    crouch = 6,
    crouching = 8,
    light1 = 10,
    light2 = 12,
    light3 = 14,
    heavy1 = 16,
    heavy2 = 18,
    heavy3 = 20,
    crouch_light1 = 22,
    crouch_light2 = 24,
    crouch_light3 = 26,
    crouch_heavy1 = 28,
    crouch_heavy2 = 30,
    crouch_heavy3 = 32,
    skill1 = 34,
    skill2 = 36,
    skill3 = 38,
    ultimate = 40,
    damaged = 42,
    startle = 44,
    fall = 46,
    win = 48,
    block_stand = 50,
    block_crouch = 52,
    fluke_horse = 54,
    fluke_horse_walk = 56
};

#define left 0;
#define right 1;

typedef struct FighterAnim{
    // Animation* idle_left;
    // Animation* idle_right;
    // Animation* walk_left;
    // Animation* walk_right;
    // Animation* jump_left;
    // Animation* jump_right;
    // Animation* crouch_left;
    // Animation* crouch_right;
    // Animation* crouching_left;
    // Animation* crouching_right;
    // Animation* light1_left;
    // Animation* light1_right;
    // Animation* light2_left;
    // Animation* light2_right;
    // Animation* light3_left;
    // Animation* light3_right;
    // Animation* heavy1_left;
    // Animation* heavy1_right;
    // Animation* heavy2_left;
    // Animation* heavy2_right;
    // Animation* heavy3_left;
    // Animation* heavy3_right;
    // Animation* crouch_light1_left;
    // Animation* crouch_light1_right;
    // Animation* crouch_light2_left;
    // Animation* crouch_light2_right;
    // Animation* crouch_light3_left;
    // Animation* crouch_light3_right;
    // Animation* crouch_heavy1_left;
    // Animation* crouch_heavy1_right;
    // Animation* crouch_heavy2_left;
    // Animation* crouch_heavy2_right;
    // Animation* crouch_heavy3_left;
    // Animation* crouch_heavy3_right;
    // Animation* skill1_left;
    // Animation* skill1_right;
    // Animation* skill2_left;
    // Animation* skill2_right;
    // Animation* skill3_left;
    // Animation* skill3_right;
    // Animation* ultimate_left;
    // Animation* ultimate_right;
    // Animation* damaged_left;
    // Animation* damaged_right;
    // Animation* startle_left;
    // Animation* startle_right;
    // Animation* fall_left;
    // Animation* fall_right;
    // Animation* win_left; // These comments are outdated, the array is used directly
    // Animation* win_right; // These comments are outdated, the array is used directly
    Animation* anims[58]; // Increased size to accommodate new animation types
    
} FighterAnim;

FighterAnim* create_fighteranim();
void destroy_fighteranim(FighterAnim* a);
void assign_anim(FighterAnim* a, int index, Animation* animation);
void play_animation(Entity* entity, FighterAnim* a, float* framecounter, int index, int side);
void play_animation_once(Entity* entity, FighterAnim* a, float* framecounter, int index, int side, int start, int stop, void (*on_complete)(void));
void reset_animation_frame(FighterAnim* a, int index);