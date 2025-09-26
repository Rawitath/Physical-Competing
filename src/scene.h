#define ADD_ENTITY_SUCCESS 0
#define ADD_SCENE_SUCCESS 0
#define REMOVE_ENTITY_SUCCESS 0
#define REMOVE_SCENE_SUCCESS 0
#define REMOVE_ENTITY_NOT_EXIST 1
#define REMOVE_SCENE_NOT_EXIST 1
#define ADD_ENTITY_ALREADY_EXIST 1
#define ADD_SCENE_ALREADY_EXIST 1

typedef struct Entity Entity;

typedef struct Scene{
    unsigned int id;
    Entity **entities;
    unsigned int entityCount;
} Scene;

Scene* create_scene();
int add_entity(Scene* scene, Entity* entity);
int remove_entity(Scene* scene, Entity* entity);
Entity* get_entity_by_index(Scene* scene, int index);
void destroy_scene(Scene* scene);

typedef struct SceneManager{
    Scene** scenes;
    Scene* activeScene;
    unsigned int sceneCount;
} SceneManager;

SceneManager* create_scene_manager();
int add_scene(SceneManager* sm, Scene* scene);
int remove_scene(SceneManager* sm, Scene* scene);
void destroy_scene_manager(SceneManager* sm);
