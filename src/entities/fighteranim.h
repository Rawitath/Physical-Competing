typedef struct Animation Animation;
typedef struct Entity Entity;

#define idle 0
#define walk 2
#define jump 4
#define crouch 6
#define crouching 8
#define light1 10
#define light2 12
#define light3 14
#define heavy1 16
#define heavy2 18
#define heavy3 20
#define crouch_light1 22
#define crouch_light2 24
#define crouch_light3 26
#define crouch_heavy1 28
#define crouch_heavy2 30
#define crouch_heavy3 32
#define skill1 34
#define skill2 36
#define skill3 38
#define ultimate 40
#define damaged 42
#define startle 44
#define fall 46
#define win 48
#define block_stand 50
#define block_crouch 52

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
    Animation* anims[54]; // Increased size to accommodate new animation types
    
} FighterAnim;

FighterAnim* create_fighteranim();
void destroy_fighteranim(FighterAnim* a);
void assign_anim(FighterAnim* a, int index, Animation* animation);
void play_animation(Entity* entity, FighterAnim* a, float* framecounter, int index, int side);
void reset_animation_frame(FighterAnim* a, int index);