#include "initiation_and_control.h"

//SCREEN, RENDERER
//
const int SCREEN_WIDTH = 720;                                    //EDIT THIS TO CHANGE SCREEN WIDTH
const int SCREEN_HEIGHT = 500;                                   //EDIT THIS TO CHANGE SCREEN HEIGHT
const std::string SCREEN_NAME = "Shrimpy Revenge";     //EDIT THIS TO CHANGE SCREEN NAME
//
SDL_Renderer* renderer;
//
m_window window;

//FONT CONSTANTS
TTF_Font* fonts[TOTAL_FONTS];

//EVENT AND KEYBOUNCE
SDL_Event e;
bool key_bounce;
bool overbutton_bounce;

//FRAME CONSTANTS
const int MAX_FPS = 60;
const int MAX_TICKS = 1000/MAX_FPS;

//ROOM AND ROOM FLAGS
room* rooms;
//
int current_room;
int room_display;
int* room_event_list;

//GAME CONTROLLER

int current_level;
int mouse_state;
int bridge_select;

int red_quantity;
int yellow_quantity;
int green_quantity;
int purple_quantity;

std::vector<point> safe_spots;
std::vector<point> empty_spots;
std::vector<point> bad_spots;
std::vector<point> red_bridges;
std::vector<point> yellow_bridges;
std::vector<point> green_bridges;
std::vector<point> purple_bridges;
point destination;
point shrimp;


void set_mouse_state(int mouse_request, int bridge_request){
    //FOR REDUNDANT CLICKS
    //
    if (mouse_state == mouse_request && bridge_select == bridge_request){
        mouse_state = 0;
        bridge_select = 0;
    } else {
        mouse_state = mouse_request;
        bridge_select = bridge_request;
    }
}

int search_empty_spot(int x_pos, int y_pos){
    for (int i = 0; i < int(empty_spots.size());i++)
        if (empty_spots[i].get_x() == x_pos && empty_spots[i].get_y() == y_pos)
            return i;

    return -1;
}

int check_position(int x_pos, int y_pos){
    point test_point = point(x_pos,y_pos);
    int position_flag = 0, i = 0;

    //CHECK THROUGH NORMAL PATHS
    //
    for (; i < int(safe_spots.size());i++)
        if (test_point.get_x() == safe_spots[i].get_x() && test_point.get_y() == safe_spots[i].get_y())
            position_flag = 1;

    //CHECK THROUGH BAD PATHS
    //
    for (i = 0; i < int(bad_spots.size());i++)
        if (test_point.get_x() == bad_spots[i].get_x() && test_point.get_y() == bad_spots[i].get_y())
            position_flag = 2;

    //CHECK THROUGH RED PATHS
    //
    for (i = 0; i < int(red_bridges.size());i++)
        if (test_point.get_x() == red_bridges[i].get_x() && test_point.get_y() == red_bridges[i].get_y())
            position_flag = 3;

    //CHECK THROUGH YELLOW PATHS
    //
    for (i = 0; i < int(yellow_bridges.size());i++)
        if (test_point.get_x() == yellow_bridges[i].get_x() && test_point.get_y() == yellow_bridges[i].get_y())
            position_flag = 4;

    //CHECK THROUGH GREEN PATHS
    //
    for (i = 0; i < int(green_bridges.size());i++)
        if (test_point.get_x() == green_bridges[i].get_x() && test_point.get_y() == green_bridges[i].get_y())
            position_flag = 5;

    //CHECK THROUGH PURPLE PATHS
    //
    for (i = 0; i < int(purple_bridges.size());i++)
        if (test_point.get_x() == purple_bridges[i].get_x() && test_point.get_y() == purple_bridges[i].get_y())
            position_flag = 6;

    if (test_point.get_x() == destination.get_x() && test_point.get_y() == destination.get_y())
        position_flag = 7;

    return position_flag;
}

bool remove_quantity(int color){
    switch (color){
        case 1:
            if (red_quantity > 0){
                red_quantity--;
                return true;
            } else
                return false;
        break;
        case 2:
        if (yellow_quantity > 0){
            yellow_quantity--;
            return true;
        } else
            return false;
        break;
        case 3:
        if (green_quantity > 0){
            green_quantity--;
            return true;
        } else
            return false;
        break;
        case 4:
            if (purple_quantity > 0){
                purple_quantity--;
                return true;
            } else
                return false;
        break;
    }

    return false;
}

void set_quantities(int red = 0, int yellow = 0, int green = 0, int purple = 0){
    red_quantity = red;
    yellow_quantity = yellow;
    green_quantity = green;
    purple_quantity = purple;
}

void unload_elements(){
    int i;
    //REMOVING SAFE SPOT IMAGES
    //
    for (i = 0; i < int(safe_spots.size());i++)
        rooms[ROOM_TWO].interfaces[1].remove_image_spot(1,point(50*safe_spots[i].get_x(),50*safe_spots[i].get_y()));
    //REMOVING EMPTY SPOT IMAGES
    //
    for (i = 0; i < int(empty_spots.size());i++)
        rooms[ROOM_TWO].interfaces[1].remove_image_spot(2,point(50*empty_spots[i].get_x(),50*empty_spots[i].get_y()));
    //REMOVING BAD SPOT IMAGES
    //
    for (i = 0; i < int(bad_spots.size());i++){
        rooms[ROOM_TWO].interfaces[1].remove_image_spot(3,point(50*bad_spots[i].get_x(),50*bad_spots[i].get_y()));
        rooms[ROOM_TWO].interfaces[1].remove_image_spot(5,point(50*bad_spots[i].get_x(),50*bad_spots[i].get_y()));
    }
    //REMOVING RED BRIDGE IMAGES
    //
    for (i = 0; i < int(red_bridges.size());i++)
        rooms[ROOM_TWO].interfaces[1].remove_image_spot(6,point(50*red_bridges[i].get_x(),50*red_bridges[i].get_y()));
    //REMOVING YELLOW BRIDGE IMAGES
    //
    for (i = 0; i < int(yellow_bridges.size());i++)
        rooms[ROOM_TWO].interfaces[1].remove_image_spot(7,point(50*yellow_bridges[i].get_x(),50*yellow_bridges[i].get_y()));
    //REMOVING GREEN BRIDGE IMAGES
    //
    for (i = 0; i < int(green_bridges.size());i++)
        rooms[ROOM_TWO].interfaces[1].remove_image_spot(8,point(50*green_bridges[i].get_x(),50*green_bridges[i].get_y()));
    //REMOVING PURPLE BRIDGE IMAGES
    //
    for (i = 0; i < int(purple_bridges.size());i++)
        rooms[ROOM_TWO].interfaces[1].remove_image_spot(9,point(50*purple_bridges[i].get_x(),50*purple_bridges[i].get_y()));
    //REMOVING DESTINATION
    //
    rooms[ROOM_TWO].interfaces[1].remove_image_spot(4,point(50*destination.get_x(),50*destination.get_y()));
    //REMOVING SHRIMP
    //
    rooms[ROOM_TWO].interfaces[1].remove_image_spot(10,point(50*shrimp.get_x(),50*shrimp.get_y()));
}

void load_elements(){
    int i;
    //ADDING SAFE SPOT IMAGES
    //
    for (i = 0; i < int(safe_spots.size());i++)
        rooms[ROOM_TWO].interfaces[1].add_image_spot(1,point(50*safe_spots[i].get_x(),50*safe_spots[i].get_y()));
    //ADDING EMPTY SPOT IMAGES
    //
    for (i = 0; i < int(empty_spots.size());i++)
        rooms[ROOM_TWO].interfaces[1].add_image_spot(2,point(50*empty_spots[i].get_x(),50*empty_spots[i].get_y()));
    //ADDING BAD SPOT IMAGES
    //
    for (i = 0; i < int(bad_spots.size());i++){
        rooms[ROOM_TWO].interfaces[1].add_image_spot(3,point(50*bad_spots[i].get_x(),50*bad_spots[i].get_y()));
        rooms[ROOM_TWO].interfaces[1].add_image_spot(5,point(50*bad_spots[i].get_x(),50*bad_spots[i].get_y()));
    }
    //ADDING DESTINATION
    //
    rooms[ROOM_TWO].interfaces[1].add_image_spot(4,point(50*destination.get_x(),50*destination.get_y()));
    //ADDING SHRIMP
    //
    rooms[ROOM_TWO].interfaces[1].add_image_spot(10,point(50*shrimp.get_x(),50*shrimp.get_y()));
}

void unload_level(){
    unload_elements();
    //CLEARING STACKS
    //
    safe_spots.clear();
    bad_spots.clear();
    empty_spots.clear();
    red_bridges.clear();
    yellow_bridges.clear();
    green_bridges.clear();
    purple_bridges.clear();
    //SETTING THESE OUT OF SIGHT
    //
    destination.set_x(-2);
    destination.set_y(-2);
    shrimp.set_x(-2);
    shrimp.set_y(-2);
}

void load_level(int level){
    //UNLOADING ANY ELEMENTS BEFOREHAND
    //
    unload_level();

    //LOADING THE LEVEL
    //
    std::cout << "Loading level " << level << std::endl;

    switch(level){
    case 1:
        safe_spots.push_back(point(2,3));
        safe_spots.push_back(point(2,4));
        safe_spots.push_back(point(2,5));
        safe_spots.push_back(point(2,6));
        safe_spots.push_back(point(3,6));
        safe_spots.push_back(point(4,3));
        safe_spots.push_back(point(4,6));
        safe_spots.push_back(point(4,8));
        safe_spots.push_back(point(5,3));
        safe_spots.push_back(point(5,4));
        safe_spots.push_back(point(5,5));
        safe_spots.push_back(point(5,8));
        safe_spots.push_back(point(6,1));
        safe_spots.push_back(point(6,3));
        safe_spots.push_back(point(6,6));

        safe_spots.push_back(point(7,3));
        safe_spots.push_back(point(7,5));
        safe_spots.push_back(point(7,6));
        safe_spots.push_back(point(8,1));
        safe_spots.push_back(point(8,5));
        safe_spots.push_back(point(9,1));
        safe_spots.push_back(point(9,5));
        safe_spots.push_back(point(10,1));
        safe_spots.push_back(point(10,2));
        safe_spots.push_back(point(10,4));

        empty_spots.push_back(point(3,3));
        empty_spots.push_back(point(5,6));
        empty_spots.push_back(point(6,2));
        empty_spots.push_back(point(7,4));
        empty_spots.push_back(point(10,5));

        bad_spots.push_back(point(7,1));

        shrimp.set_x(3);
        shrimp.set_y(6);

        destination.set_x(10);
        destination.set_y(3);

        set_quantities(1,2,0,0);
    break;
    case 2:
        safe_spots.push_back(point(1,1));
        safe_spots.push_back(point(1,2));
        safe_spots.push_back(point(1,3));
        safe_spots.push_back(point(1,4));
        safe_spots.push_back(point(1,5));
        safe_spots.push_back(point(1,6));
        safe_spots.push_back(point(3,2));
        safe_spots.push_back(point(3,4));
        safe_spots.push_back(point(3,5));
        safe_spots.push_back(point(3,6));
        safe_spots.push_back(point(3,7));
        safe_spots.push_back(point(4,7));
        safe_spots.push_back(point(5,1));
        safe_spots.push_back(point(5,3));
        safe_spots.push_back(point(5,7));
        safe_spots.push_back(point(6,4));
        safe_spots.push_back(point(6,5));
        safe_spots.push_back(point(6,7));
        safe_spots.push_back(point(7,1));
        safe_spots.push_back(point(7,4));
        safe_spots.push_back(point(8,1));
        safe_spots.push_back(point(8,2));
        safe_spots.push_back(point(8,4));
        safe_spots.push_back(point(8,5));
        safe_spots.push_back(point(8,6));
        safe_spots.push_back(point(9,2));
        safe_spots.push_back(point(9,6));
        safe_spots.push_back(point(10,2));
        safe_spots.push_back(point(10,6));
        safe_spots.push_back(point(11,2));
        safe_spots.push_back(point(11,6));
        safe_spots.push_back(point(12,1));
        safe_spots.push_back(point(12,2));
        safe_spots.push_back(point(12,3));
        safe_spots.push_back(point(12,5));
        safe_spots.push_back(point(12,6));

        empty_spots.push_back(point(2,2));
        empty_spots.push_back(point(2,6));
        empty_spots.push_back(point(3,3));
        empty_spots.push_back(point(4,4));
        empty_spots.push_back(point(5,4));
        empty_spots.push_back(point(6,1));
        empty_spots.push_back(point(6,6));
        empty_spots.push_back(point(8,3));
        empty_spots.push_back(point(12,4));

        bad_spots.push_back(point(3,2));
        bad_spots.push_back(point(12,1));

        shrimp.set_x(6);
        shrimp.set_y(7);

        destination.set_x(5);
        destination.set_y(2);

        set_quantities(1,1,2,0);
    break;
    case 3:
        safe_spots.push_back(point(1,1));
        safe_spots.push_back(point(1,2));
        safe_spots.push_back(point(1,3));
        safe_spots.push_back(point(1,4));
        safe_spots.push_back(point(1,5));
        safe_spots.push_back(point(1,6));
        safe_spots.push_back(point(1,7));
        safe_spots.push_back(point(2,1));
        safe_spots.push_back(point(2,3));
        safe_spots.push_back(point(2,7));
        safe_spots.push_back(point(3,1));
        safe_spots.push_back(point(3,6));
        safe_spots.push_back(point(3,7));
        safe_spots.push_back(point(4,1));
        safe_spots.push_back(point(4,2));
        safe_spots.push_back(point(4,3));
        safe_spots.push_back(point(4,4));
        safe_spots.push_back(point(4,7));
        safe_spots.push_back(point(5,2));
        safe_spots.push_back(point(5,4));
        safe_spots.push_back(point(5,7));
        safe_spots.push_back(point(6,1));
        safe_spots.push_back(point(6,3));
        safe_spots.push_back(point(6,4));
        safe_spots.push_back(point(6,5));
        safe_spots.push_back(point(6,7));
        safe_spots.push_back(point(7,1));
        safe_spots.push_back(point(7,4));
        safe_spots.push_back(point(8,2));
        safe_spots.push_back(point(8,3));
        safe_spots.push_back(point(8,4));
        safe_spots.push_back(point(8,5));
        safe_spots.push_back(point(8,7));
        safe_spots.push_back(point(9,1));
        safe_spots.push_back(point(9,4));
        safe_spots.push_back(point(10,1));
        safe_spots.push_back(point(10,7));
        safe_spots.push_back(point(11,2));
        safe_spots.push_back(point(11,4));
        safe_spots.push_back(point(11,5));
        safe_spots.push_back(point(11,6));
        safe_spots.push_back(point(11,7));
        safe_spots.push_back(point(12,1));

        empty_spots.push_back(point(3,3));
        empty_spots.push_back(point(6,2));
        empty_spots.push_back(point(6,6));
        empty_spots.push_back(point(8,1));
        empty_spots.push_back(point(8,6));
        empty_spots.push_back(point(9,7));
        empty_spots.push_back(point(10,4));
        empty_spots.push_back(point(11,1));
        empty_spots.push_back(point(11,3));

        bad_spots.push_back(point(2,3));
        bad_spots.push_back(point(5,2));
        bad_spots.push_back(point(12,1));

        shrimp.set_x(8);
        shrimp.set_y(4);

        destination.set_x(3);
        destination.set_y(5);

        set_quantities(1,1,2,1);
    break;
    }

    load_elements();
}

void change_level(int new_level){
    if (new_level > 3){
        //THIS IMPLIES ALL LEVELS HAVE BEEN COMPLETED
        //
        std::cout << "Levels completed!" << std::endl;

        room_display = ROOM_THREE;
    } else {
        current_level = new_level;
        load_level(new_level);
    }

    set_mouse_state(0,0);
}

void move_camera(int direction){
    //std::cout << "MOVING CAMERA" << std::endl;
    if (room_display == 1)
        switch (direction){
        case 0:
            rooms[ROOM_TWO].interfaces[0].updating_camera(-5,0);
        break;
        case 1:
            rooms[ROOM_TWO].interfaces[0].updating_camera(5,0);
        break;
    }
}

void move_shrimp(int direction){
    int x_move = 0, y_move = 0, move_flag;

    //CHECKING DIRECTION, AND CHECKING IF THERE IS A VIABLE TILE ON A PATH
    //
    switch (direction){
        case 0:
        //MOVING LEFT
        //
            x_move = -1;
            if ((move_flag = check_position(shrimp.get_x()+x_move,shrimp.get_y())) > 0)
                rooms[ROOM_TWO].interfaces[1].update_image(10,4,1);
        break;
        case 1:
        //MOVING UP
        //
            y_move = -1;
            if ((move_flag = check_position(shrimp.get_x(),shrimp.get_y()+y_move)) > 0)
                rooms[ROOM_TWO].interfaces[1].update_image(10,1,1);
        break;
        case 2:
        //MOVING DOWN
        //
            y_move = 1;
            if ((move_flag = check_position(shrimp.get_x(),shrimp.get_y()+y_move)) > 0)
                rooms[ROOM_TWO].interfaces[1].update_image(10,2,1);
        break;
        case 3:
        //MOVING RIGHT
        //
            x_move = 1;
            if ((move_flag = check_position(shrimp.get_x()+x_move,shrimp.get_y())) > 0)
                rooms[ROOM_TWO].interfaces[1].update_image(10,3,1);
        break;
    }

    //CHECKING THE PATH RULES
    //

    switch (move_flag){
        case 1:
            //MOVE ONTO THE SAFE TILE (MOVE NORMALLY)
            //
            rooms[ROOM_TWO].interfaces[1].move_image_spot(10,point(50*shrimp.get_x(),50*shrimp.get_y()),50*x_move,50*y_move);
            shrimp.set_x(shrimp.get_x()+x_move);
            shrimp.set_y(shrimp.get_y()+y_move);
        break;
        case 2:
            //MOVE ONTO THE BAD TILE
            //
            load_level(current_level);
        break;
        case 3:
            //MOVE ONTO THE RED TILE (MOVE ABSOLUTE LEFT)
            //
            rooms[ROOM_TWO].interfaces[1].move_image_spot(10,point(50*shrimp.get_x(),50*shrimp.get_y()),50*x_move,50*y_move);
            shrimp.set_x(shrimp.get_x()+x_move);
            shrimp.set_y(shrimp.get_y()+y_move);
            move_shrimp(0);
        break;
        case 4:
            //MOVE ONTO THE YELLOW TILE (MOVE ABSOLUTE UP)
            //
            rooms[ROOM_TWO].interfaces[1].move_image_spot(10,point(50*shrimp.get_x(),50*shrimp.get_y()),50*x_move,50*y_move);
            shrimp.set_x(shrimp.get_x()+x_move);
            shrimp.set_y(shrimp.get_y()+y_move);
            move_shrimp(1);
        break;
        case 5:
            //MOVE ONTO THE GREEN TILE (MOVE ABSOLUTE DOWN)
            //
            rooms[ROOM_TWO].interfaces[1].move_image_spot(10,point(50*shrimp.get_x(),50*shrimp.get_y()),50*x_move,50*y_move);
            shrimp.set_x(shrimp.get_x()+x_move);
            shrimp.set_y(shrimp.get_y()+y_move);
            move_shrimp(2);
        break;
        case 6:
            //MOVE ONTO THE PURPLE TILE (MOVE ABSOLUTE RIGHT)
            //
            rooms[ROOM_TWO].interfaces[1].move_image_spot(10,point(50*shrimp.get_x(),50*shrimp.get_y()),50*x_move,50*y_move);
            shrimp.set_x(shrimp.get_x()+x_move);
            shrimp.set_y(shrimp.get_y()+y_move);
            move_shrimp(3);
        break;
        case 7:
            //MOVE ONTO THE DESTINATION TILE (NEXT LEVEL)
            //
            current_level++;
            change_level(current_level);
        break;
    }
}

void bridge_build(){
    if (bridge_select > 0 && mouse_state == 1){
        int mouse_x, mouse_y, empty_spot;

        SDL_GetMouseState(&mouse_x,&mouse_y);

        //MODIFY MOUSE POSITION IN CONTEXT TO THE GRID
        //
        mouse_x/=50;
        mouse_y-=100;
        mouse_y/=50;
        //std::cout << mouse_x << " " << mouse_y << std::endl;

        //CHECK IF THE POSITION IS A VALID EMPTY SPOT
        //
        if ((empty_spot = search_empty_spot(mouse_x,mouse_y)) > -1){
            //CHECK IF THERE IS A VALID NUMBER OF A CERTAIN BRIDGE
            //
            switch (bridge_select){
                case 1:
                    if (remove_quantity(bridge_select)){
                        red_bridges.push_back(point(mouse_x,mouse_y));
                        rooms[ROOM_TWO].interfaces[1].add_image_spot(6,point(mouse_x*50,mouse_y*50));
                        rooms[ROOM_TWO].interfaces[1].remove_image_spot(2,point(mouse_x*50,mouse_y*50));
                        empty_spots.erase(empty_spots.begin() + empty_spot);
                    }
                break;
                case 2:
                    if (remove_quantity(bridge_select)){
                        yellow_bridges.push_back(point(mouse_x,mouse_y));
                        rooms[ROOM_TWO].interfaces[1].add_image_spot(7,point(mouse_x*50,mouse_y*50));
                        rooms[ROOM_TWO].interfaces[1].remove_image_spot(2,point(mouse_x*50,mouse_y*50));
                        empty_spots.erase(empty_spots.begin() + empty_spot);
                    }
                break;
                case 3:
                    if (remove_quantity(bridge_select)){
                        green_bridges.push_back(point(mouse_x,mouse_y));
                        rooms[ROOM_TWO].interfaces[1].add_image_spot(8,point(mouse_x*50,mouse_y*50));
                        rooms[ROOM_TWO].interfaces[1].remove_image_spot(2,point(mouse_x*50,mouse_y*50));
                        empty_spots.erase(empty_spots.begin() + empty_spot);
                    }
                break;
                case 4:
                    if (remove_quantity(bridge_select)){
                        purple_bridges.push_back(point(mouse_x,mouse_y));
                        rooms[ROOM_TWO].interfaces[1].add_image_spot(9,point(mouse_x*50,mouse_y*50));
                        rooms[ROOM_TWO].interfaces[1].remove_image_spot(2,point(mouse_x*50,mouse_y*50));
                        empty_spots.erase(empty_spots.begin() + empty_spot);
                    }
                break;
            }

            std::cout << red_quantity << " " << yellow_quantity << " " << green_quantity << " " << purple_quantity << std::endl;
        }

        //RESETTING THE STATE
        //
        mouse_state = bridge_select = 0;
    }
}

int main(int argc,char *argv[]){
    //INITIALIZING VARIABLES
    //
    key_bounce = false;
    overbutton_bounce = false;
    shrimp = point();
    destination = point();
    current_level = mouse_state = bridge_select = 0;
    set_quantities();

    //IF QUITTING APPLICATION
    bool quit = false;

    //FRAME COUNT
    float avg_FPS;
    int counted_frames = 0;

    //TIMER COUNT AND FLAGS
    Uint32 previous_ticks = 0;
    bool timer_play = true, pause_play = false;

    //ROOM VARIABLES
    current_room = -1;
    room_display = ROOM_ONE;

    //INITIALIZING WINDOW AND SDL ElEMENTS
    window = m_window();
    timer main_timer = timer();
    timer cap_timer = timer();
    main_timer.play();

    if (!initialize()){
        std::cout << "Failed to initialize!" << std::endl;
        quit = true;
    } else {
        //CONSTRUCT ROOMS
        //
        rooms = new room[ROOM_TOTAL];

        for (int i = 0; i < ROOM_TOTAL; i++)
            rooms[i] = room();

        //LOADING ALL THE ROOM CONTENTS
        //
        std::cout << "Loading rooms: " << std::endl;

        if (!load_rooms()){
            std::cout << "Failed to load rooms!" << std::endl;
            quit = true;
        } else {
            //PIVOT TEST
            //
            std::cout << "Loaded rooms successfully!" << std::endl;

            //****GAME LOOP (UNTIL GAME QUITS)
            //
            while (!quit){

                //PRE EVENT LOOP STUFF
                //
                avg_FPS = counted_frames / (main_timer.get_ticks()/1000.f);

                if (avg_FPS > 2000.0)
                    avg_FPS = 0.0;

                //STARTING CAP TIMER
                //
                cap_timer.play();

                //ROOM CHECKER (IN CASE ROOM CHANGED)
                //
                if (current_room != room_display){
                    //DEACTIVATE THE OLD ROOM (ASSUMING CURRENT ROOM HAS ACTUALLY BEEN INITIATED AND REFERRING TO A REAL ROOM ADDRESS)
                    //
                    if (current_room > -1)
                        rooms[current_room].deactivate_room(current_room);

                    //SET THE NEW CURRENT ROOM
                    //
                    if (room_display < 0)
                        current_room = 0;
                    else if (room_display < ROOM_TOTAL)
                        current_room = room_display;
                    else
                        current_room = ROOM_TOTAL-1;

                    //LOAD ROOM INTERFACES AND OTHER ELEMENTS
                    //
                    if (!(rooms[current_room].has_realtime))
                        main_timer.stop();
                    else
                        main_timer.play();
                        previous_ticks = main_timer.get_ticks();

                    //ACTIVATE THE NEW ROOM
                    //
                    rooms[current_room].activate_room(current_room);
                }

                //TIMER CONTROLLER (IN CASE PLAYING OR PAUSED)
                //
                if (pause_play && main_timer.get_playing())
                    main_timer.pause();
                else if (timer_play && !(main_timer.get_playing()))
                    main_timer.play();

                //EVENT LOOP (UNTIL THERE IS NOTHING TO POLL)
                //
                while (SDL_PollEvent(&e) != 0){
                    //QUIT EVENT
                    //
                    if (e.type == SDL_QUIT)
                        quit = true;

                    //KEY EVENTS
                    //
                    const Uint8* current_key_state = SDL_GetKeyboardState(NULL);

                    if (!key_bounce){
                        if (current_key_state[SDL_SCANCODE_A]){
                            if (mouse_state < 2)
                                move_camera(0);
                            else
                                move_shrimp(0);
                        }
                        if (current_key_state[SDL_SCANCODE_W]){
                            if (mouse_state > 1)
                                move_shrimp(1);
                        }
                        if (current_key_state[SDL_SCANCODE_S]){
                            if (mouse_state > 1)
                                move_shrimp(2);
                        }
                        if (current_key_state[SDL_SCANCODE_D]){
                            if (mouse_state < 2)
                                move_camera(1);
                            else
                                move_shrimp(3);
                        }

                        key_bounce = true;
                    }

                    delete current_key_state;

                    //
                    //POLLING WINDOW AND MOUSE CLICK EVENTS
                    //
                    room_event_list = rooms[current_room].event_listen(e);

                    switch (current_room){
                        case ROOM_ONE:
                            if (room_event_list[0] == 1){
                                rooms[ROOM_ONE].interfaces[0].play_sound(0);
                                rooms[ROOM_ONE].interfaces[0].update_image(1,4,1);
                                room_display = ROOM_TWO;
                                set_mouse_state(0,0);
                                change_level(1);
                            } else if (room_event_list[0] == 2){
                                rooms[ROOM_ONE].interfaces[0].update_image(1,3,1);
                            } else if (room_event_list[0] == 3){
                                if (!overbutton_bounce){
                                    rooms[ROOM_ONE].interfaces[0].play_sound(1);
                                    rooms[ROOM_ONE].interfaces[0].update_image(1,2,1);
                                    overbutton_bounce = true;
                                }
                            } else {
                                rooms[ROOM_ONE].interfaces[0].update_image(1,1,1);
                                overbutton_bounce = false;
                            }
                        break;
                        case ROOM_TWO:
                            if (room_event_list[0] == 1){
                                //BE ABLE TO BUILD A RED BRIDGE
                                //
                                rooms[ROOM_TWO].interfaces[0].play_sound(0);
                                rooms[ROOM_TWO].interfaces[0].update_image(1,4,1);
                                set_mouse_state(1,1);
                            } else if (room_event_list[0] == 2){
                                rooms[ROOM_TWO].interfaces[0].update_image(1,3,1);
                            } else if (room_event_list[0] == 3){
                                rooms[ROOM_TWO].interfaces[0].update_image(1,2,1);
                            } else {
                                rooms[ROOM_TWO].interfaces[0].update_image(1,1,1);
                            }

                            if (room_event_list[0] == 5){
                                //BE ABLE TO BUILD A YELLOW BRIDGE
                                //
                                rooms[ROOM_TWO].interfaces[0].play_sound(0);
                                rooms[ROOM_TWO].interfaces[0].update_image(2,4,1);
                                set_mouse_state(1,2);
                            } else if (room_event_list[0] == 6){
                                rooms[ROOM_TWO].interfaces[0].update_image(2,3,1);
                            } else if (room_event_list[0] == 7){
                                rooms[ROOM_TWO].interfaces[0].update_image(2,2,1);
                            } else {
                                rooms[ROOM_TWO].interfaces[0].update_image(2,1,1);
                            }

                            if (room_event_list[0] == 9){
                                //BE ABLE TO BUILD A GREEN BRIDGE
                                //
                                rooms[ROOM_TWO].interfaces[0].play_sound(0);
                                rooms[ROOM_TWO].interfaces[0].update_image(3,4,1);
                                set_mouse_state(1,3);
                            } else if (room_event_list[0] == 10){
                                rooms[ROOM_TWO].interfaces[0].update_image(3,3,1);
                            } else if (room_event_list[0] == 11){
                                rooms[ROOM_TWO].interfaces[0].update_image(3,2,1);
                            } else {
                                rooms[ROOM_TWO].interfaces[0].update_image(3,1,1);
                            }

                            if (room_event_list[0] == 13){
                                //BE ABLE TO BUILD A PURPLE BRIDGE
                                //
                                rooms[ROOM_TWO].interfaces[0].play_sound(0);
                                rooms[ROOM_TWO].interfaces[0].update_image(4,4,1);
                                set_mouse_state(1,4);
                            } else if (room_event_list[0] == 14){
                                rooms[ROOM_TWO].interfaces[0].update_image(4,3,1);
                            } else if (room_event_list[0] == 15){
                                rooms[ROOM_TWO].interfaces[0].update_image(4,2,1);
                            } else {
                                rooms[ROOM_TWO].interfaces[0].update_image(4,1,1);
                            }

                            if (room_event_list[0] == 17){
                                //START MOVING THE SHRIMP (SAVE THIS FOR LAST)
                                //
                                rooms[ROOM_TWO].interfaces[0].play_sound(0);
                                rooms[ROOM_TWO].interfaces[0].update_image(5,4,1);
                                set_mouse_state(2,0);
                            } else if (room_event_list[0] == 18){
                                rooms[ROOM_TWO].interfaces[0].update_image(5,3,1);
                            } else if (room_event_list[0] == 19){
                                rooms[ROOM_TWO].interfaces[0].update_image(5,2,1);
                            } else {
                                rooms[ROOM_TWO].interfaces[0].update_image(5,1,1);
                            }

                            if (room_event_list[0] == 21){
                                //RESET THE LEVEL
                                //
                                rooms[ROOM_TWO].interfaces[0].play_sound(0);
                                rooms[ROOM_TWO].interfaces[0].update_image(6,4,1);
                                set_mouse_state(0,0);
                                load_level(current_level);
                            } else if (room_event_list[0] == 22){
                                rooms[ROOM_TWO].interfaces[0].update_image(6,3,1);
                            } else if (room_event_list[0] == 23){
                                rooms[ROOM_TWO].interfaces[0].update_image(6,2,1);
                            } else {
                                rooms[ROOM_TWO].interfaces[0].update_image(6,1,1);
                            }

                            if (room_event_list[1] == 1)
                                bridge_build();
                        break;
                        case ROOM_THREE:
                            if (room_event_list[0] == 1){
                                rooms[ROOM_THREE].interfaces[0].play_sound(0);
                                quit = true;
                            } else if (room_event_list[0] == 2){
                                rooms[ROOM_THREE].interfaces[0].update_image(1,3,1);
                            } else if (room_event_list[0] == 3){
                                if (!overbutton_bounce){
                                    rooms[ROOM_THREE].interfaces[0].play_sound(1);
                                    rooms[ROOM_THREE].interfaces[0].update_image(1,2,1);
                                    overbutton_bounce = true;
                                }
                            } else {
                                rooms[ROOM_THREE].interfaces[0].update_image(1,1,1);
                                overbutton_bounce = false;
                            }
                        break;
                    }

                    delete[] room_event_list;
                }

                //UPDATING ROOM AND ROOM ELEMENTS
                //
                if (rooms[current_room].has_realtime){
                    rooms[current_room].update(main_timer.get_ticks() - previous_ticks);
                    previous_ticks = main_timer.get_ticks();
                }


                //RENDERING CURRENT ROOM
                //
                rooms[current_room].render();
                SDL_RenderPresent(renderer);

                //CHECKING AND MANAGING FPS
                //
                if (!(main_timer.get_paused()) && (main_timer.get_playing()))
                    ++counted_frames;

                if (MAX_TICKS < cap_timer.get_ticks()){
                    //std::cout << "WAITING FOR COUNTER TO CATCH UP BY:" << (cap_timer.get_ticks() - MAX_TICKS) << std::endl;
                    SDL_Delay(cap_timer.get_ticks() - MAX_TICKS);
                }

                //CLEARING KEY BOUNCE
                //
                if (key_bounce)
                    key_bounce = false;
            }

            unload_level();

            safe_spots.~vector();
            empty_spots.~vector();
            bad_spots.~vector();
            red_bridges.~vector();
            yellow_bridges.~vector();
            green_bridges.~vector();
            purple_bridges.~vector();

            shrimp.~point();
            destination.~point();

            close();
        }

        delete[] rooms;
    }
    //
    //END OF PROGRAM
    return 0;
}
