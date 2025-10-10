#include "sc_process.h"
#include "scenecontroller.h"
#include "scene.h"

void sc_load_scene(int index)
{
    if(getSceneManager() != 0){
        load_scene(getSceneManager(), index);
    }
}