#include <z_media/text.h>

text::~text(){
    wipe();
    color.~SDL_Color();
}

void text::wipe(){
    if (texture != NULL)
        SDL_DestroyTexture(texture);
}

Uint8 text::get_red(){
    return color.r;
}

void text::set_red(Uint8 new_red){
    color.r = new_red;
}

Uint8 text::get_green(){
    return color.g;
}

void text::set_green(Uint8 new_green){
    color.g = new_green;
}

Uint8 text::get_blue(){
    return color.b;
}

void text::set_blue(Uint8 new_blue){
    color.b = new_blue;
}

Uint8 text::get_alpha(){
    return color.a;
}

void text::set_alpha(Uint8 new_alpha){
    color.a = new_alpha;
}

void text::load_text(int font, int scale){
    wipe();
    SDL_Surface* first_text = NULL;

    first_text = TTF_RenderText_Solid(fonts[font],content.c_str(),color);

    if (first_text == NULL && texture == NULL){
        std::cout << "Failed to load text: " << TTF_GetError() << std::endl;
    } else {
        texture = SDL_CreateTextureFromSurface(renderer,first_text);
        x_size = first_text->w*scale;
        y_size = first_text->h*scale;

        if (texture == NULL){
            std::cout << "Failed to load text onto texture: " << TTF_GetError() << std::endl;
        }

        SDL_FreeSurface(first_text);
    }
}

void text::render(int x,int y){
    if (is_active){
        //Rectangles for rendering
        //
        //Frame of text itself
        SDL_Rect render_frame = {0,0,x_size,y_size};
        //Frame of position and text
        //
        SDL_Rect render_position = {x,y,x_size,y_size};
        //
        //
        SDL_RenderCopy(renderer,texture,&render_frame,&render_position);
    }
}

std::string text::get_content(){
    return content;
}

void text::set_content(std::string new_content){
    //Setting new string for content
    //
    content = new_content;
}

int text::get_x_size(){
    return x_size;
}

int text::get_y_size(){
    return y_size;
}

void text::set_active(bool new_active){
    is_active = new_active;
}

bool text::get_active(){
    return is_active;
}

int text::get_element_ID(){
    return element_ID;
}

void text::set_element_ID(int new_element_ID){
    element_ID = new_element_ID;
}

int text::compare_element_ID(text text_obs){
    return element_ID - text_obs.get_element_ID();
}

int text::compare_to(text text_obs){
    int compare_num = compare_element_ID(text_obs);

    if (compare_num == 0)
        return (content.compare(text_obs.get_content().c_str()));
    else
        return compare_num;
}
