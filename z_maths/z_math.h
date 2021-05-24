#ifndef Z_MATH_H_INCLUDED
#define Z_MATH_H_INCLUDED

#include <iostream>
#include <vector>
#include <random>
#include <functional>

#include "../z_maths/event_rectangle.h"

struct event_cluster{
public:
    event_cluster(int index = 0, bool active = false){element_ID = index; is_active = active;};
    ~event_cluster(){event_rectangles.clear(); event_circles.clear(); event_rectangles.~vector(); event_circles.~vector();};
    //HITBOX ACTIONS
    //
    void move_clusters(int x_move = 0,int y_move = 0);
    bool is_contact(event_cluster other_cluster);
    //ID COMPARER
    //
    int compare_to(event_cluster other_cluster);

    std::vector<event_rectangle> event_rectangles;
    std::vector<event_circle> event_circles;

    int element_ID;
    bool is_active;
};

//COORDINATE STUFF
//
class point{
public:
    point(int new_x = 0, int new_y = 0){
    x = new_x;
    y = new_y;};

    ~point(){};

    int get_x(){return x;};
    void set_x(int new_x = 0){x = new_x;};

    int get_y(){return y;};
    void set_y(int new_y = 0){y = new_y;};

private:
    int x,y;
};

//ROUNDING FUNCTIONS
//
float rounding(float num = 0.f);
double rounding(double num = 0.d);

//MOD FUNCTIONS FOR DOUBLE AND FLOAT
//
float mod_float(float num1 = 0.f, int num2 = 0);
double mod_double(double num1 = 0.d, int num2 = 0);

//SEARCHING THROUGH STACKS (OBJECTS INDENTIFIED BY INT)
//
int lin_search_num(int num_stack[] = {}, int low_b = 0, int max_b = -1, int num = 0);
int lin_search_num(std::vector<int>& num_stack, int num = 0);

int bin_search_num(int num_stack[] = {}, int low_b = 0, int max_b = -1, int num = 0);
int bin_search_num(std::vector<int>& num_stack, int low_b = 0, int max_b = -1,int num = 0);

#include "timer.h"

#include "camera.h"

#include "button.h"

#include "int_reader.h"

#endif // Z_MATH_H_INCLUDED
