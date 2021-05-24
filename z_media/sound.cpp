#include <z_media/sound.h>

sound::sound(int ind){
    chunk = NULL;
    is_active = false;
    element_ID = ind;
}

sound::~sound(){
    wipe();
}

bool sound::load_sound(std::string sound_id){
    bool load_flag = true;

    if (!(chunk = Mix_LoadWAV(sound_id.c_str()))){
        std::cout << "Failed to load sound: " << Mix_GetError() << std::endl;
        load_flag = false;
    }

    return load_flag;
}

void sound::wipe(){
    if (chunk != NULL)
        Mix_FreeChunk(chunk);
}

void sound::play(){
    if (chunk != NULL)
        Mix_PlayChannel(-1,chunk,0);
    else
        std::cout << "Failed to play sound: " << Mix_GetError() << std::endl;

}

bool sound::get_active(){
    return is_active;
}

void sound::set_active(bool active){
    is_active = active;
}

int sound::get_element_ID(){
    return element_ID;
}

void sound::set_element_ID(int new_element_ID){
    element_ID = new_element_ID;
}

int sound::compare_element_ID(sound sound_obs){
    return element_ID - sound_obs.get_element_ID();
}
