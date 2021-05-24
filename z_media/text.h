#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

enum font_types{
    NO_FONT = 0,
    ANDYFISH,
    FISHSAUSAGES,
    TOTAL_FONTS
};

extern SDL_Renderer* renderer;
extern TTF_Font* fonts[TOTAL_FONTS];

class text{
public:
    //Constructor
    //
    //extended
    text(std::string content, int r,int g,int b, int ind){
        //LOADING BASE VARIABLES
        //
        texture = NULL;
        color.r = r;
        color.g = g;
        color.b = b;
        content = content;
        x_size = y_size = 0;
        is_active = false;
        //
        element_ID = ind;
    };
    //quick
    text(std::string content = "", int ind = 0):text(content,0,0,0,ind){};
    //Destructor
    //
    ~text();
    //Wiping text
    //
    void wipe();
    //Color accessors and mutators
    //
    //red
    Uint8 get_red();
    void set_red(Uint8 new_red = 0);
    //green
    Uint8 get_green();
    void set_green(Uint8 new_green = 0);
    //blue
    Uint8 get_blue();
    void set_blue(Uint8 new_blue = 0);
    //alpha
    Uint8 get_alpha();
    void set_alpha(Uint8 new_alpha = 0);
    //Loading text
    //
    void load_text(int font = NO_FONT, int scale = 1);
    //Render text at a certain place
    //
    void render(int x = 0, int y = 0);
    //Content accessors and mutators
    //
    std::string get_content();
    void set_content(std::string new_content);
    //SIZE ACCESSORS
    //
    int get_x_size();
    int get_y_size();
    //Is Active accessors and mutators
    //
    bool get_active();
    void set_active(bool new_active = false);
    //Element ID managers
    //
    int get_element_ID();
    void set_element_ID(int new_element_ID = 0);
    int compare_element_ID(text text_obs = text());
    //COMPARER
    //
    int compare_to(text text_obs);

private:
    SDL_Texture* texture;
    //Color being used
    //
    SDL_Color color;
    //Text's contents
    //
    std::string content;
    //Dimensions of text
    //
    int x_size, y_size;
    //If text is active
    //
    bool is_active;
    //Reference ID
    //
    int element_ID;
};

#endif // TEXT_H_INCLUDED
