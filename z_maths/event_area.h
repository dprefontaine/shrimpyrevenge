#ifndef EVENT_AREA_H_INCLUDED
#define EVENT_AREA_H_INCLUDED

class event_area{
public:
    //Constructor
    event_area(int new_x_pos = 0, int new_y_pos = 0){
        x_pos = new_x_pos;
        y_pos = new_y_pos;
    };
    //Destructor
    ~event_area(){};
    //Position accessor and mutators
    //
    //x
    int get_x_pos(){return x_pos;};
    void set_x_pos(int new_x_pos = 0){x_pos = new_x_pos;};
    //y
    int get_y_pos(){return event_area::y_pos;};
    void set_y_pos(int new_y_pos = 0){y_pos = new_y_pos;};

private:
    int x_pos, y_pos;
};

#endif // EVENT_AREA_H_INCLUDED
