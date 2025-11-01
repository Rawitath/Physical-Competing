typedef struct Entity Entity;

Entity* leftFighter;
void leftFighter_init();
void leftFighter_subtract_break(int val);
void leftFighter_add_break(int val);
void leftFighter_subtract_health(int val);
void leftFighter_add_health(int val);
void leftFighter_subtract_ultimate(int val);
void leftFighter_add_ultimate(int val);
void leftFighter_destroy();