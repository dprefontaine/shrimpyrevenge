#include <z_maths/timer.h>

timer::timer(int ind){
    timer::play_ticks = 0;
    timer::pause_ticks = 0;
    timer::is_playing = false;
    timer::is_paused = true;
    //
    timer::element_ID = ind;
}

timer::~timer(){

}

void timer::play(){
    timer::is_playing = true;
    timer::is_paused = false;

    timer::play_ticks = SDL_GetTicks();
    timer::pause_ticks = 0;
}

void timer::pause(){
    if (timer::is_playing && !(timer::is_paused)){
        timer::is_paused = true;

        timer::pause_ticks = SDL_GetTicks() - timer::play_ticks;
        timer::play_ticks = 0;
    }
}

void timer::unpause(){
    if (timer::is_playing && timer::is_paused){
        timer::is_playing = true;
        timer::is_paused = false;

        timer::play_ticks = SDL_GetTicks() - timer::pause_ticks;
        timer::pause_ticks = 0;
    }
}

void timer::stop(){
    timer::is_playing = false;
    timer::is_paused = false;

    timer::play_ticks = 0;
    timer::pause_ticks = 0;
}

void timer::reset(){
    timer::pause();
    timer::unpause();
}

Uint32 timer::get_ticks(){
    Uint32 time = 0;

    if (timer::is_playing){
        if (timer::is_paused){
            time = timer::pause_ticks;
        } else {
            time = SDL_GetTicks() - timer::play_ticks;
        }
    }

    return time;
}

bool timer::get_playing(){
    return timer::is_playing;
}

bool timer::get_paused(){
    return timer::is_paused;
}

int timer::get_element_ID(){
    return timer::element_ID;
}

void timer::set_element_ID(int new_element_ID){
    timer::element_ID = new_element_ID;
}

int timer::compare_element_ID(timer timer_obs){
    return timer::element_ID - timer_obs.get_element_ID();
}
