#include "tweener.h"
#include <stdio.h>
#include <stdlib.h>

void linear_tween_to(float* value, float to, float speed, int direction)
{
   if (direction == 1) { // Add until value exceeds 'to'
    if(*value + speed >= to){
        *value = to;
        return;
    }
        if (*value < to) {
            *value += speed;
        }
    } else { // Subtract until value is less than 'to'
        if(*value - speed <= to){
        *value = to;
        return;
    }
        if (*value > to) {
            *value -= speed;
        }
    }
}

void linear_tween_to_int(int* value, int to, float speed, int direction)
{
    if (direction == 1) { // Add until value exceeds 'to'
        if(*value + speed >= to){
        *value = to;
        return;
    }
        if (*value < to) {
            *value += speed;
        }
    } else { // Subtract until value is less than 'to'
        if(*value - speed <= to){
        *value = to;
        return;
    }
        if (*value > to) {
            *value -= speed;
        }
    }
}
