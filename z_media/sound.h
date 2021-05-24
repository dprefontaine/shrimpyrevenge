#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <iostream>

class sound {
public:
    //Constructor
    //
    sound(int ind = 0);
    //Destructor
    //
    ~sound();
    //Load sound
    //
    bool load_sound(std::string sound_id = "sounds/button_click.wav");
    //Wipe sound
    //
    void wipe();
    //Play
    //
    void play();
    //ACTIVE
    //
    bool get_active();
    void set_active(bool active = false);
    //ID ACCESSORS, MUTATORS, AND COMPARERS
    //
    int get_element_ID();
    void set_element_ID(int new_element_ID = 0);
    int compare_element_ID(sound sound_obs);

private:
    Mix_Chunk *chunk;
    //
    //
    bool is_active;
    int element_ID;
};

#endif // SOUND_H_INCLUDED
