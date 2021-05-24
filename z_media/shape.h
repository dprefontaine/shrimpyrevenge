#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include <SDL.h>
#include <iostream>
#include <string>

//This doesn't require index as for now

enum shape_types{
    SHAPE_NONE,
    SHAPE_LINE,
    SHAPE_RECTANGLE,
    SHAPE_CIRCLE,
    SHAPE_TOTAL
};

enum shape_styles{
    STYLE_NONE,
    STYLE_FILL,
    STYLE_OUTLINE,
    STYLE_FILL_AND_OUTLINE,
    STYLE_TOTAL
};

//FOR RENDERING PURPOSES
//
extern SDL_Renderer* renderer;

class shape{
public:
    //CONSTRUCTORS
    //
    //extended
    shape(int new_shape_type, int new_shape_style, int new_x_size, int new_y_size, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha, int index){
        shape_type = new_shape_type;
        shape_style = new_shape_style;
        active = false;
        x_size = new_x_size;
        y_size = new_y_size;
        shape_color = {red,green,blue,alpha};
        element_ID = index;
    };
    //quick
    shape(int shape_type = SHAPE_NONE, int x_size = 1, int y_size = 1, int index = 0):shape(shape_type, STYLE_NONE, x_size, y_size, 255, 255, 255, 255, index){};
    //standard
    shape(int new_shape_type, int new_x_size, int new_y_size, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha, int index):shape(new_shape_type, STYLE_NONE, new_x_size, new_y_size, red, green, blue, alpha, index){};
    //DESTRUCTOR
    //
    ~shape();
    //RENDERING SHAPE
    //
    void render(int x = 0, int y = 0);
    //TYPE ACCESSOR AND MUTATOR
    //
    int get_shape();
    void set_shape(int new_shape = SHAPE_NONE);

    //STYLE ACCESSOR AND MUTATOR
    //
    int get_style();
    void set_style(int new_style = STYLE_NONE);

    //SIZE ACCESSOR AND MUTATOR
    //
    int get_x_size();
    void set_x_size(int new_x_size = 1);

    int get_y_size();
    void set_y_size(int new_y_size = 1);

    //COLOR ACCESSORS AND MUTATORS
    //
    Uint8 get_red();
    void set_red(Uint8 new_red = 0);

    Uint8 get_green();
    void set_green(Uint8 new_green = 0);

    Uint8 get_blue();
    void set_blue(Uint8 new_blue = 0);

    Uint8 get_alpha();
    void set_alpha(Uint8 new_alpha = 0);
    //
    //
    bool get_active();
    void set_active(bool new_active);
    //Element ID manager
    //
    int get_element_ID();
    void set_element_ID(int new_element_ID = 0);
    //Shape comparer
    //
    int compare_to(shape other_shape = shape());
    int compare_element_ID(shape shape_obs = shape());

private:
    //SHAPE TYPE AND STYLE (SEE ENUMERATION)
    //
    int shape_type, shape_style;
    //
    bool active;
    //SIZE OF SHAPE
    //
    int x_size, y_size;
    //COLOR OF SHAPE
    //
    SDL_Color shape_color;
    //Reference ID
    //
    int element_ID;
};

#endif // SHAPE_H_INCLUDED
