#ifndef JOBPAPER_H
#define JOBPAPER_H

typedef struct Entity Entity;

extern Entity* jobpaper;
void jobpaper_init();
void release_jobpaper(Entity* fighter, int direction);

#endif // JOBPAPER_H
