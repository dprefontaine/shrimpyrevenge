#ifndef EVENT_RECTANGLE_H_INCLUDED
#define EVENT_RECTANGLE_H_INCLUDED

#include "event_circle.h"

//NOTE: THIS IS ALL REFERRING TO PIXEL COORDINATES
//

class event_rectangle: public event_area{
public:
    using event_area::event_area;
    //Constructor
    event_rectangle(int x_pos = 0,int y_pos = 0,int x_size = 0, int y_size = 0) : event_area(x_pos,y_pos){
        event_rectangle::x_size = x_size;
        event_rectangle::y_size = y_size;
    };
    //Destructor
    ~event_rectangle(){};
    //Size accessors and mutators
    //
    //x
    int get_x_size();
    void set_x_size(int new_x_size = 0);
    //y
    int get_y_size();
    void set_y_size(int new_y_size = 0);
    //
    //Compare
    //
    int compare_to(event_rectangle other_rect);
    bool check_collision(event_rectangle other_rect);
    bool check_collision(event_circle other_circ);

private:
    int x_size, y_size;
};

#endif // EVENT_RECTANGLE_H_INCLUDED
