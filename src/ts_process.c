#include "ts_process.h"
#include <SDL3/SDL.h>

Uint64 current;
Uint64 previous;
double ts_delta;

void ts_init(){
    current = SDL_GetPerformanceCounter();
    previous = 0;
    ts_delta = 0;
}

void ts_renderdeltatime()
{
    previous = current;
    current = SDL_GetPerformanceCounter();
}

void ts_setdeltatime()
{
    ts_delta = (current - previous) / (double)SDL_GetPerformanceFrequency();
}

double ts_getdelta(){
    return ts_delta;
}

double ts_gettime(){
    return current / (double)SDL_GetPerformanceFrequency();
}
