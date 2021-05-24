#include <z_media/shape.h>

shape::~shape(){
    shape_color.~SDL_Color();
}

void shape::render(int x,int y){
    SDL_SetRenderDrawColor(renderer,shape_color.r,shape_color.g,shape_color.b,shape_color.a);
    SDL_Rect draw_rect = {x,y,x_size,y_size};

    switch (shape_type){
        case SHAPE_NONE:
            SDL_RenderDrawPoint(renderer,draw_rect.x,draw_rect.y);
        break;
        case SHAPE_LINE:
            SDL_RenderDrawLine(renderer,draw_rect.x,draw_rect.y,draw_rect.x+x_size,draw_rect.y+y_size);
        break;
        case SHAPE_RECTANGLE:
            switch (shape_style){
                case STYLE_NONE:
                case STYLE_FILL:
                    SDL_RenderFillRect(renderer,&draw_rect);
                break;
                case STYLE_OUTLINE:
                    SDL_RenderDrawRect(renderer,&draw_rect);
                break;
                case STYLE_FILL_AND_OUTLINE:
                    SDL_RenderFillRect(renderer,&draw_rect);
                    SDL_SetRenderDrawColor(renderer,shape_color.r-(shape_color.r/10),shape_color.g-(shape_color.g/10),shape_color.b-(shape_color.b/10),shape_color.a-(shape_color.a/10));
                    SDL_RenderDrawRect(renderer,&draw_rect);
                break;
            }
        break;
    }
}

int shape::get_shape(){
    return shape_type;
}

void shape::set_shape(int new_shape){
    shape_type = new_shape;
}

int shape::get_style(){
    return shape_style;
}

void shape::set_style(int new_style){
    shape_style = new_style;
}

int shape::get_x_size(){
    return x_size;
}

void shape::set_x_size(int new_x_size){
    x_size = new_x_size;
}

int shape::get_y_size(){
    return y_size;
}

void shape::set_y_size(int new_y_size){
    y_size = new_y_size;
}

Uint8 shape::get_red(){
    return shape_color.r;
}

void shape::set_red(Uint8 new_red){
    shape_color.r = new_red;
}

Uint8 shape::get_green(){
    return shape_color.g;
}

void shape::set_green(Uint8 new_green){
    shape_color.g = new_green;
}

Uint8 shape::get_blue(){
    return shape_color.b;
}

void shape::set_blue(Uint8 new_blue){
    shape_color.b = new_blue;
}

Uint8 shape::get_alpha(){
    return shape_color.a;
}

void shape::set_alpha(Uint8 new_alpha){
    shape_color.a = new_alpha;
}

bool shape::get_active(){
    return active;
}

void shape::set_active(bool new_active){
    active = new_active;
}

int shape::get_element_ID(){
    return element_ID;
}

void shape::set_element_ID(int new_element_ID){
    element_ID = new_element_ID;
}

int shape::compare_to(shape other_shape){
    int compare_num;

    if ((compare_num = compare_element_ID(other_shape)) == 0)
        if ((compare_num = shape_type - other_shape.get_shape()) == 0)
            if ((compare_num = shape_style - other_shape.get_style()) == 0)
                if ((compare_num = x_size - other_shape.get_x_size()) == 0)
                    return y_size - other_shape.get_y_size();
                else
                    return compare_num;
            else
                return compare_num;
        else
            return compare_num;
    else
        return compare_num;
}

int shape::compare_element_ID(shape shape_obs){
    return element_ID - shape_obs.get_element_ID();
}
