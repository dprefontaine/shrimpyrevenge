#ifndef INITIATION_AND_CONTROL_H_INCLUDED
#define INITIATION_AND_CONTROL_H_INCLUDED

#include "z_mechanics/z_mechanics.h"
#include "room.h"

extern const std::string SCREEN_NAME;
extern m_window window;
extern room* rooms;
extern int current_room;

//INITIALIZATION AND CLOSING FUNCTIONS
//
bool initialize();
void close();
bool load_rooms();

//CONTROL FUNCTIONS
//


#endif // INITIATION_H_INCLUDED
