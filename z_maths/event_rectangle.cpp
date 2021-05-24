#include <z_maths/event_rectangle.h>

int event_rectangle::get_x_size(){
    return event_rectangle::x_size;
}

void event_rectangle::set_x_size(int new_x_size){
    event_rectangle::x_size = new_x_size;
}

int event_rectangle::get_y_size(){
    return event_rectangle::y_size;
}

void event_rectangle::set_y_size(int new_y_size){
    event_rectangle::y_size = new_y_size;
}

int event_rectangle::compare_to(event_rectangle other_rect){
    int compare_flag = event_rectangle::get_x_pos() - other_rect.get_x_pos();

    if (compare_flag == 0)
        if ((compare_flag = event_rectangle::get_y_pos() - other_rect.get_y_pos()) == 0)
            if ((compare_flag = x_size - other_rect.get_x_size()) == 0)
                return y_size - other_rect.get_y_size();
            else
                return compare_flag;
        else
            return compare_flag;
    else
        return compare_flag;
}

bool event_rectangle::check_collision(event_rectangle other_rect){
    //Check if minimum of this rectangle is above the other rectangle's maximum
    //
    //AND
    //
    //Check if maximum of this rectangle is below the other rectangle's minimum
    //
    //X AXIS (above or below)
    //
    if ((event_rectangle::get_x_pos() > (other_rect.get_x_size() + other_rect.get_x_pos())) || ((event_rectangle::get_x_pos() + event_rectangle::get_x_size()) < other_rect.get_x_pos()))
        return false;
    //Y AXIS (above or below)
    //
    if ((event_rectangle::get_y_pos() > (other_rect.get_y_size() + other_rect.get_y_pos())) || ((event_rectangle::get_y_pos() + event_rectangle::get_y_size()) < other_rect.get_y_pos()))
        return false;

    return true;
}

bool event_rectangle::check_collision(event_circle other_circ){
    //
    //a^2 + b^2 = c^2
    //
    //
    //
    int closest_x,closest_y;

    //finding closest x point for a

    if (event_rectangle::get_x_pos()+event_rectangle::x_size < other_circ.get_x_pos()){
        //away to the right of the rectangle
        closest_x = event_rectangle::get_x_pos() + event_rectangle::x_size;
    } else if (event_rectangle::get_x_pos() > other_circ.get_x_pos()){
        //away to the left of the rectangle
        closest_x = event_rectangle::get_x_pos();
    } else {
        //within the rectangle's x bounds
        closest_x = other_circ.get_x_pos();
    }
    //finding closest y point for b

    if (event_rectangle::get_y_pos()+event_rectangle::y_size < other_circ.get_y_pos()){
        //away above the rectangle
        closest_y = event_rectangle::get_y_pos() + event_rectangle::y_size;
    } else if (event_rectangle::get_y_pos() > other_circ.get_y_pos()){
        //away below the rectangle
        closest_y = event_rectangle::get_y_pos();
    } else {
        //within the rectangle's y bounds
        closest_y = other_circ.get_y_pos();
    }

    int closest_point = int_magnitude(closest_x-other_circ.get_x_pos(),closest_y-other_circ.get_y_pos());

    //c^2
    //
    int rad_squared_other = int_magnitude(other_circ.get_radius(),0);

    if (closest_point > rad_squared_other)
        return false;
    else
        return true;
}
