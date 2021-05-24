#ifndef IMAGES_H_INCLUDED
#define IMAGES_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

//FOR RENDERING PURPOSES
//
extern SDL_Renderer* renderer;

class image{
public:
    //Constructors
    //
    //extended construct
    image(int new_x_size,int new_y_size,int new_x_clip,int new_y_clip,
          int new_max_state,int new_max_frame,
          double new_orientation,
          Uint8 red, Uint8 green, Uint8 blue, Uint8 transparency,
          int ind){
            //SPRITESHEET OF IMAGE
            //
            texture = NULL;
            //
            is_active = false;
            //DIMENSIONS OF SPRITE SHEET
            //
            x_size = new_x_size;
            y_size = new_y_size;
            //DIMENSIONS OF EACH CLIP
            //
            x_clip = new_x_clip;
            y_clip = new_y_clip;
            //STATES
            //
            current_state = 1;
            current_state_max = new_max_state;
            //FRAME SEQUENCES
            //
            current_frame = 1;
            current_frame_max = new_max_frame;
            //
            current_clip.x = 0;
            current_clip.y = 0;
            current_clip.w = new_x_clip;
            current_clip.h = new_y_clip;
            //Orientation
            //
            image_orientation = new_orientation;
            //Color offset
            //
            color_and_transparency.r = red;
            color_and_transparency.g = green;
            color_and_transparency.b = blue;
            color_and_transparency.a = transparency;
            //Index
            //
            element_ID = ind;
        }
    //quick construct
    image(int new_x_size = 1,int new_y_size = 1,int ind = 0):image(new_x_size, new_y_size, new_x_size, new_y_size, 1, 1, 0.0, 255, 255, 255, 0, ind){};
    //standard construct
    image(int new_x_size,int new_y_size,int new_x_clip,int new_y_clip,int new_max_state,int new_max_frame, int ind):image(new_x_size, new_y_size, new_x_clip, new_y_clip, new_max_state, new_max_frame, 0.0, 255, 255, 255, 0, ind){};
    //Destructor
    //
    ~image();
    //Clean image from renderer
    //
    void wipe();
    //Load image to renderer
    //
    bool load_image(std::string image_path);
    //Render image
    //
    void render(int x = 0, int y = 0);
    //
    //
    void set_blend_mode(SDL_BlendMode blend_mode = SDL_BLENDMODE_NONE);
    //Size accessors and mutators
    //
    //x
    int get_x_size();
    void set_x_size(int new_x_size = 1);
    //y
    int get_y_size();
    void set_y_size(int new_y_size = 1);
    //Clipping accessors and mutators
    //
    //x
    int get_x_clip();
    void set_x_clip(int new_x_clip = 1);
    //y
    int get_y_clip();
    void set_y_clip(int new_y_clip = 1);
    //State accessors and mutators
    //
    int get_state();
    void set_state(int new_state = 0);
    //Clip accessors and mutators
    //
    int get_frame();
    void set_frame(int new_frame = 0);
    //Orientation accessors and mutators
    //
    double get_orientation();
    void set_orientation(double new_orientation = 0.0);
    //Color and transparency accessors and mutators
    //
    //Red
    Uint8 get_red();
    void set_red(Uint8 new_red = 0);
    //Green
    Uint8 get_green();
    void set_green(Uint8 new_green = 0);
    //Blue
    Uint8 get_blue();
    void set_blue(Uint8 new_blue = 0);
    //Transparency
    Uint8 get_transparency();
    void set_transparency(Uint8 new_transparency = 0);
    //ACTIVE ACCESSOR AND MUTATOR
    //
    void set_active(bool new_active = false);
    bool get_active();
    //Clip updater
    //
    void update_clip();
    //Element ID manager
    //
    int get_element_ID();
    void set_element_ID(int new_element_ID = 0);
    int compare_element_ID(image image_obs = image());
    //COMPARER
    //
    int compare_to(image image_obs);

private:
    SDL_Texture* texture;
    //
    bool is_active;
    //Size of the whole sprite sheet
    //
    int x_size, y_size;
    //Size of a sprite clipping
    //
    int x_clip, y_clip;
    //Transparency and color offset
    //
    SDL_Color color_and_transparency;
    //Orientation of an image
    //
    double image_orientation;
    //States read vertically, and clips read horizontally
    //
    int current_state, current_state_max;
    int current_frame, current_frame_max;
    //Final result from clipping
    //
    SDL_Rect current_clip;
    //Reference ID
    //
    int element_ID;
};

#endif // IMAGES_H_INCLUDED
