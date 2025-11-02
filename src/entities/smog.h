#ifndef SMOG_H
#define SMOG_H

#include "../entity.h"

extern Entity* smog;

void smog_init();
void release_smog(Entity* fighter);

#endif // SMOG_H