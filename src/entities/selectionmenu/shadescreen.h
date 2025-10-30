#pragma once
typedef struct Entity Entity;

Entity* shadescreen;
void shadescreen_init();
extern int shadescreen_alpha;
void shadescreen_set(int state);