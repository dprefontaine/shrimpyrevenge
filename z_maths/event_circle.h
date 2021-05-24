#ifndef EVENT_CIRCLE_H_INCLUDED
#define EVENT_CIRCLE_H_INCLUDED

#include "event_area.h"

//MAGNITUDE
//
int int_magnitude(int x, int y);

//NOTE: THIS IS ALL REFERRING TO PIXEL COORDINATES
//

class event_circle: public event_area{
public:
    //Constructor
    event_circle(int x_pos = 0,int y_pos = 0,int radius = 0) : event_area(x_pos,y_pos){
        event_circle::radius = radius;
    };
    //Destructor
    ~event_circle(){};
    //Radius accessor and mutator
    //
    int get_radius();
    void set_radius(int new_radius = 0);
    //
    //Compare
    //
    int compare_to(event_circle other_circ);
    bool check_collision(event_circle other_circ);

private:
    int radius;
};

#endif // EVENT_CIRCLE_H_INCLUDED
