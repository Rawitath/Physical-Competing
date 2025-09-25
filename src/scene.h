#define ADD_ENTITY_SUCCESS 0
#define REMOVE_ENTITY_SUCCESS 0
#define REMOVE_ENTITY_NOT_EXIST 1
#define ADD_ENTITY_ALREADY_EXIST 1

typedef struct Entity Entity;

typedef struct Scene{
    unsigned int id;
    Entity **entities;
    unsigned int entityCount;
} Scene;

void init_scene(Scene* scene, unsigned int id);
int add_entity(Scene* scene, Entity* entity);
int remove_entity(Scene* scene, Entity* entity);