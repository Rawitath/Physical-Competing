#include "../entity.h"
#include "soundtester.h"
#include "../timesystem.h"
#include "../scene.h"
#include "../scenecontroller.h"
#include "../soundsystem.h"
#include <stdio.h>
#include "../animation.h"

#include <SDL3/SDL.h>

void soundtester_start();
void soundtester_poll(SDL_Event* event);
void soundtester_loop();
void soundtester_render(SDL_Renderer* renderer);
void soundtester_destroy();

void soundtester_init(){
    soundtester = create_entity(
            NULL,
            &soundtester_start,
            &soundtester_poll,
            &soundtester_loop,
            &soundtester_render,
            &soundtester_destroy
        );
}

Audio* music;

void soundtester_start(){
    music = create_audio("res/music/muteonerising.wav");
    music->loop = SET_LOOP_ONCE;
}
void soundtester_poll(SDL_Event* event){
    if(event->type == SDL_EVENT_KEY_DOWN){
        if(event->key.scancode == SDL_SCANCODE_0){
            play_audio(music, RESET_TRUE);
        }
        if(event->key.scancode == SDL_SCANCODE_9){
            pause_audio(music);
        }
        if(event->key.scancode == SDL_SCANCODE_8){
            stop_audio(music);
        }
    }
}

void soundtester_loop(){
    
}
void soundtester_render(SDL_Renderer* renderer){
    render_entity(soundtester, renderer, NULL);
}
void soundtester_destroy(){
    destroy_audio(music);
    destroy_entity(soundtester);
}
