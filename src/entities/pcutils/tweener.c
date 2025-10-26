#include "tweener.h"
#include <stdio.h>

void linear_tween_to(float* value, float to, float speed, float threshold)
{
    if(*value - to > -threshold && *value - to < threshold) return;
    if(*value - to < -threshold){
        *value += speed;
    }
    else if(*value - to > threshold){
        *value -= speed;
    }
}
