typedef struct Entity Entity;
typedef enum CharacterState CharacterState;

Entity* rightFighter;
void rightFighter_init();
void rightFighter_subtract_break(int val);
void rightFighter_add_break(int val);
void rightFighter_subtract_health(int val);
void rightFighter_add_health(int val);
void rightFighter_subtract_ultimate(int val);
void rightFighter_add_ultimate(int val);
void rightFighter_destroy();

extern CharacterState rightFighter_currentState;
extern int rightFighter_facingRight;
extern float rightFighter_stateTimer;