#include "sc_process.h"
#include "scene.h"

SceneManager* sc_sm = 0;

void sc_init(SceneManager* _sm)
{
    sc_sm = _sm;
}

SceneManager* getSceneManager(){
    return sc_sm;
}
