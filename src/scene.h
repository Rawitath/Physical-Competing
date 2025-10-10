#define ADD_ENTITY_SUCCESS 0
#define ADD_SCENE_SUCCESS 0
#define REMOVE_ENTITY_SUCCESS 0
#define REMOVE_SCENE_SUCCESS 0
#define REMOVE_ENTITY_NOT_EXIST 1
#define REMOVE_ENTITY_ALLOCATION_FAILED 2
#define REMOVE_SCENE_NOT_EXIST 1
#define REMOVE_SCENE_ALLOCATION_FAILED 2
#define ADD_ENTITY_ALREADY_EXIST 1
#define ADD_ENTITY_ALLOCATION_FAILED 2
#define ADD_SCENE_ALREADY_EXIST 1
#define ADD_SCENE_ALLOCATION_FAILED 2
#define LOAD_SCENE_OUT_OF_BOUND 1
#define LOAD_SCENE_SUCCESS 0

#define GET_ENTITY_OUT_OF_BOUND NULL
#define GET_ENTITY_NOT_FOUND NULL
#define GET_SCENE_OUT_OF_BOUND NULL
#define GET_SCENE_NOT_FOUND NULL

#define UI_REFERENCE_X 100
#define UI_REFERENCE_Y 100

typedef struct Entity Entity;

typedef struct Scene{
    unsigned int id;
    const char* name;
    Entity **entities;
    unsigned int entityCount;
    float viewportX;
    float viewportY;
    float viewportZoom;
    
    void (*load)();
    void (*unload)();
} Scene;

Scene* create_scene(void (*load)(), void (*unload)());
int add_entity(Scene* scene, Entity* entity);
int remove_entity(Scene* scene, Entity* entity);
Entity* get_entity_by_index(Scene* scene, int index);
Entity* get_entity_by_id(Scene* scene, int id);
Entity* get_entity_by_name(Scene* scene, const char* name);
void destroy_scene(Scene* scene);

typedef struct SceneManager{
    Scene** scenes;
    Scene* activeScene;
    unsigned int sceneCount;
} SceneManager;

SceneManager* create_scene_manager();
int add_scene(SceneManager* sm, Scene* scene);
int remove_scene(SceneManager* sm, Scene* scene);
Scene* get_scene_by_index(SceneManager* sm, int index);
Scene* get_scene_by_id(SceneManager* sm, int id);
Scene* get_scene_by_name(SceneManager* sm, const char* name);
void destroy_scene(Scene* scene);
void destroy_scene_manager(SceneManager* sm);
int load_scene(SceneManager* sm, int index);
