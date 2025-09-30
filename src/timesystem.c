#include "ts_process.h"
#include "timesystem.h"

float get_delta()
{
    return (float)ts_getdelta();
}

float get_time(){
    return (float)ts_gettime();
}
