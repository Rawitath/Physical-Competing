#pragma once
typedef struct Entity Entity;

Entity* shadescreen;
void shadescreen_init();
extern int shadescreen_alpha;
void shadescreen_set(int state);
void shadescreen_set_instant(int state);