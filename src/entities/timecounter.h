typedef struct Entity Entity;

Entity* timecounter;
void timecounter_init();
void counter_set_max_time(int time);
void counter_set_time(int time);
extern int currentTime;
