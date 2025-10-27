typedef struct Entity Entity;

Entity* lefthealthbar;
void lefthealthbar_init();
void lefthealthbar_set_health(int health);
void lefthealthbar_add_health(int health);
void lefthealthbar_subtract_health(int health);
