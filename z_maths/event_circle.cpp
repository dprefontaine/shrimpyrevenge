#include <z_maths/event_circle.h>

//MAGNITUDE
//
int int_magnitude(int x, int y){
    return (x*x) + (y*y);
}

//EVENT CIRCLE

int event_circle::get_radius(){
    return radius;
}

void event_circle::set_radius(int new_radius){
    radius = new_radius;
}

int event_circle::compare_to(event_circle other_circ){
    int compare_flag = event_circle::get_x_pos() - other_circ.get_x_pos();

    if (compare_flag == 0)
        if ((compare_flag = event_circle::get_y_pos() - other_circ.get_y_pos()) == 0)
            return radius - other_circ.get_radius();
        else
            return compare_flag;
    else
        return compare_flag;
}

bool event_circle::check_collision(event_circle other_circ){
    //This is following the Pythagorean theorem
    //
    //a^2 + b^2 = c^2
    //
    //GETTING THE DISTANCE (a^2 + b^2)
    //
    int distance = int_magnitude(get_x_pos()-other_circ.get_x_pos(),get_y_pos()-other_circ.get_y_pos());

    //c^2

    int rad_squared_self = int_magnitude(radius,0);
    int rad_squared_other = int_magnitude(other_circ.get_radius(),0);

    if (distance > rad_squared_self)
        return false;

    if (distance > rad_squared_other)
        return false;

    return true;
}
