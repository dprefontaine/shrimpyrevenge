#include <z_maths/z_math.h>

//Chances are, only one of these files is needed
//Essentially, this is here to manage awkward maths like round, as well as managing vector searches
//On top of this, game mechanics and room inventories will call to these function a lot (lot)
//
//

void event_cluster::move_clusters(int x_move,int y_move){
    int i;

    for (i = 0; i < int(event_rectangles.size()); i++){
        event_rectangles[i].set_x_pos(event_rectangles[i].get_x_pos() + x_move);
        event_rectangles[i].set_y_pos(event_rectangles[i].get_y_pos() + y_move);
    }

    for (i = 0; i < int(event_circles.size()); i++){
        event_circles[i].set_x_pos(event_circles[i].get_x_pos() + x_move);
        event_circles[i].set_y_pos(event_circles[i].get_y_pos() + y_move);
    }
}

bool event_cluster::is_contact(event_cluster other_cluster){
    bool contact_flag = false;
    int i = 0, max_i = (event_rectangles.size());
    int j = (int(other_cluster.event_rectangles.size()) - 1);

    //KEEP COMPARING WHILE CONTACT FLAG IS FALSE OR BOUNDS ARE VIOLATED
    //
    //RECTANGLES ONLY
    //
    while (!(contact_flag || j < 0) && i < max_i){
        contact_flag = event_rectangles[i].check_collision(other_cluster.event_rectangles[j]);

        i++;
        //CHECKING IF NEED TO RESET
        //
        if (!(i < max_i)){
            i = 0;
            j--;
        }
    }

    j = (int(other_cluster.event_circles.size()) - 1);
    //RECTANGLE AND CIRCLES
    //
    while (!(contact_flag || j < 0) && i < max_i){
        contact_flag = event_rectangles[i].check_collision(other_cluster.event_circles[j]);

        i++;
        //CHECKING IF NEED TO RESET
        //
        if (!(i < max_i)){
            i = 0;
            j--;
        }
    }

    max_i = int(other_cluster.event_circles.size());
    j = (int(other_cluster.event_rectangles.size()) - 1);

    while (!(contact_flag || j < 0) && i < max_i){
        contact_flag = other_cluster.event_rectangles[j].check_collision(event_circles[i]);

        i++;
        //CHECKING IF NEED TO RESET
        //
        if (!(i < max_i)){
            i = 0;
            j--;
        }
    }

    j = (int(other_cluster.event_circles.size()) - 1);
    //CIRCLES ONLY
    //
    while (!(contact_flag || j < 0) && i < max_i){
        contact_flag = event_circles[i].check_collision(other_cluster.event_circles[j]);

        i++;
        //CHECKING IF NEED TO RESET
        //
        if (!(i < max_i)){
            i = 0;
            j--;
        }
    }

    return contact_flag;
}

int event_cluster::compare_to(event_cluster other_cluster){
    int compare_flag = element_ID - other_cluster.element_ID;

    //COMPARING BY ELEMENT ID
    //
    if (compare_flag == 0){
        //COMPARING BY EVENT RECTANGLES
        //
        if ((compare_flag = int(event_rectangles.size()) - int(other_cluster.event_rectangles.size())) == 0){
            //COMPARING BY EVENT CIRCLES
            //
            return int(event_circles.size()) - int(other_cluster.event_circles.size());
        } else
            return compare_flag;
    } else
        return compare_flag;
}

//ROUNDING
//
float rounding(float num){
    //ANOTHER FLOAT FOR REFERENCE
    float decimal, dummy_float;
    decimal = dummy_float = num;

    decimal = decimal - float(int(dummy_float));

    if (decimal < 0.5)
        num = float(int(num));
    else
        num = float(int(num)) + 1.f;

    return num;
}

double rounding(double num){
    //ANOTHER FLOAT FOR REFERENCE
    double decimal, dummy_float;
    decimal = dummy_float = num;

    decimal = decimal - double(int(dummy_float));

    if (decimal < 0.5)
        num = double(int(num));
    else
        num = double(int(num)) + 1.d;

    return num;
}

//MOD STUFF
//
float mod_float(float num1, int num2){
    //CHECKING IF MOD-ABLE (SO IT DOESNT ENTER INFINITE LOOP)
    if (num2 > 0)
        //KEEP SUBTRACTING FROM FLOAT
        while (num1 > num2)
            num1-=float(num2);

    return num1;
}

double mod_double(double num1, int num2){
    //CHECKING IF MOD-ABLE (SO IT DOESNT ENTER INFINITE LOOP)
    if (num2 > 0)
        //KEEP SUBTRACTING FROM DOUBLE
        while (num1 > num2)
            num1-=double(num2);

    return num1;
}

//LINEAR SEARCHING
//
int lin_search_num(int num_stack[], int low_b, int max_b, int num){
    if (max_b < low_b)
        return (-max_b);
    else
        if (num_stack[low_b] == num)
            return low_b;
        else
            return lin_search_num(num_stack,++low_b,max_b,num);
}

int lin_search_num(std::vector<int>& num_stack, int num){
    int i = num_stack.size(), j = 0;

    while (j < i){
        if (num_stack[j] == num)
            return j;
        j++;
    }

    return -j;
}

//BINARY SEARCHING
//THIS ONLY WORKS IF THEN THE STACK IS ORGANIZED
//
int bin_search_num(int num_stack[], int low_b, int max_b, int num){
    //IN CASE LOWER BOUNDS EXCEEDS MAX BOUNDS (END CASE)
    //
    if (max_b < low_b)
        return -((max_b+low_b)/2);
    else {
        //GET THE MIDDLE ELEMENT
        //
        int mid = (max_b+low_b)/2;
        //CHECK IF THE MIDDLE IS THE ELEMENT
        //
        if (num_stack[mid] == num)
            return mid;
        else if (num_stack[mid] < num)
            //INCREASE BOUNDS IF NUM IS GREATER
            //
            return bin_search_num(num_stack, ++low_b, max_b, num);
        else
            //DECREASE BOUNDS IF NUM IS LESSER
            //
            return bin_search_num(num_stack, low_b, --max_b, num);
    }
}

int bin_search_num(std::vector<int>& num_stack,int low_b,int max_b, int num){
    //IN CASE LOWER BOUNDS EXCEEDS UPPER BOUNDS (OR THE MIDDLE JUST EXCEEDS THE VECTOR SIZE)
    //
    if (low_b > max_b || int(num_stack.size()) < ((max_b+low_b)/2))
        return -((max_b+low_b)/2);
    else {
        //GET THE MIDDLE ELEMENT
        //
        int mid = (max_b+low_b)/2;
        //CHECK THE MIDDLE ELEMENT
        //
        if (num_stack.at(mid) == num)
            return mid;
        else if (num_stack.at(mid) > num)
            //INCREASE BOUNDS IF NUM IS GREATER
            //
            return bin_search_num(num_stack, ++low_b, max_b, num);
        else
            //DECREASE BOUNDS IF NUM IS LESSER
            //
            return bin_search_num(num_stack, low_b, --max_b, num);
    }
}
