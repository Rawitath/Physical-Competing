#ifndef DRILL_H
#define DRILL_H

typedef struct Entity Entity;

extern Entity* drill;
void drill_init();
void release_drill(Entity* fighter, int direction);

#endif // DRILL_H