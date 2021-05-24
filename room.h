#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include "game_interface.h"

//EDIT THIS FOR HOW MANY ROOMS YOU WANT
//
enum GAME_ROOMS{
    ROOM_ONE = 0,
    ROOM_TWO,
    ROOM_THREE,
    ROOM_TOTAL
};

extern m_window window;

struct room{
public:
    //CONSTRUCTOR
    room();
    //DESTRUCTOR
    ~room();

    //FOR LOADING INTERFACES AND REMOVING INTERFACES
    //
    bool load_room(int room_number = 0);
    void clear_room();
    //FOR ACTIVATING OR DEACTIVATING A ROOM
    //
    void activate_room(int room_number = 0);
    void deactivate_room(int room_number = 0);
    //EVENT STUFF
    //
    int* event_listen(SDL_Event& e);
    //UPDATING (W/ TIME PASSED TO IT)
    //
    void update(Uint32 ticks = 1);
    //RENDERING
    //
    void render();
    //
    //
    std::vector<game_interface> interfaces = {};
    std::vector<timer> game_timers = {};
    std::vector<file_reader> file_readers = {};

    bool is_active;
    bool has_realtime;
};

#endif // ROOM_H_INCLUDED
