typedef struct Entity Entity;
typedef enum CharacterState CharacterState;

Entity* leftFighter;
void leftFighter_init();
void leftFighter_subtract_break(int val);
void leftFighter_add_break(int val);
void leftFighter_subtract_health(int val);
void leftFighter_add_health(int val);
void leftFighter_subtract_ultimate(int val);
void leftFighter_add_ultimate(int val);
void leftFighter_destroy();

extern CharacterState leftFighter_currentState;
extern int leftFighter_facingRight;
extern float leftFighter_stateTimer;