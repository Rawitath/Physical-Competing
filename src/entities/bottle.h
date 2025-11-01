#ifndef BOTTLE_H
#define BOTTLE_H

typedef struct Entity Entity;

extern Entity* bottle;
void bottle_init();
void release_bottle(float x, float y, int direction);

#endif // BOTTLE_H