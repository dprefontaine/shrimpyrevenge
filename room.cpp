#include <room.h>

//CONSTRUCTOR
//
room::room(){
    is_active = false;
    has_realtime = false;

    interfaces = std::vector<game_interface>();
    game_timers = std::vector<timer>();
    file_readers = std::vector<file_reader>();
};

//DESTRUCTOR
//
room::~room(){
    std::cout << "Setting room inactive..." << std::endl;
    deactivate_room();
    std::cout << "Clearing room bins..." << std::endl;
    clear_room();
    std::cout << "Deleting vectors...";
    std::cout << "..interfaces...";
    interfaces.~vector();
    std::cout << "..timers...";
    game_timers.~vector();
    std::cout << "..readers...";
    file_readers.~vector();
    std::cout << "........ successfully closed!" << std::endl;
};

//LOADING MEDIA MEDIA OF ROOM (FOR INITIATION)
//
bool room::load_room(int room_number){
    bool room_flag = true;

    //EDIT THIS FOR WHATEVER INTERFACES YOU WANT TO ADD
    //
    image_bundle shrimp_bg = image_bundle();
    shrimp_bg.m_image = image(SCREEN_WIDTH,SCREEN_HEIGHT,0);
    shrimp_bg.points.push_back(point(0,0));

    image_bundle ui_bg = image_bundle();
    ui_bg.m_image = image(SCREEN_WIDTH,SCREEN_HEIGHT/5,1);
    ui_bg.points.push_back(point(0,0));
    ui_bg.points.push_back(point(720,0));

    image_bundle game_bg = image_bundle();
    game_bg.m_image = image(SCREEN_WIDTH,SCREEN_HEIGHT*4/5,2);
    game_bg.points.push_back(point(0,0));

    image_bundle game_tile = image_bundle();
    game_tile.m_image = image(50,50,4);

    image_bundle empty_tile = image_bundle();
    empty_tile.m_image = image(50,50,5);

    image_bundle bad_tile = image_bundle();
    bad_tile.m_image = image(50,50,6);

    image_bundle destination_tile = image_bundle();
    destination_tile.m_image = image(50,50,7);

    image_bundle crab = image_bundle();
    crab.m_image = image(50,50,8);

    image_bundle shrimp = image_bundle();
    shrimp.m_image = image(200,200,50,50,4,4,0.0,0xFF,0xFF,0xFF,0xFF,9);

    image_bundle slot = image_bundle();
    slot.m_image = image(50,50,10);

    image_bundle red_bridge = image_bundle();
    red_bridge.m_image = image(50,50,11);

    image_bundle yellow_bridge = image_bundle();
    yellow_bridge.m_image = image(50,50,20);

    image_bundle green_bridge = image_bundle();
    green_bridge.m_image = image(50,50,30);

    image_bundle purple_bridge = image_bundle();
    purple_bridge.m_image = image(50,50,40);

    image_bundle start_button = image_bundle();
    start_button.m_image = image(340,840,340,210,4,1,0.0,0xAA,0xDD,0xAA,0xFF,12);
    start_button.points.push_back(point(340,190));

    image_bundle red_button = image_bundle();
    red_button.m_image = image(125,300,125,75,4,1,0.0,0xFF,0x55,0x55,0xFF,21);
    red_button.points.push_back(point(20,10));

    image_bundle yellow_button = image_bundle();
    yellow_button.m_image = image(125,300,125,75,4,1,0.0,0xFF,0xFF,0x55,0xFF,22);
    yellow_button.points.push_back(point(160,10));

    image_bundle green_button = image_bundle();
    green_button.m_image = image(125,300,125,75,4,1,0.0,0x77,0xFF,0x77,0xFF,23);
    green_button.points.push_back(point(300,10));

    image_bundle purple_button = image_bundle();
    purple_button.m_image = image(125,300,125,75,4,1,0.0,0xAA,0x55,0xFF,0xFF,24);
    purple_button.points.push_back(point(440,10));

    image_bundle move_button = image_bundle();
    move_button.m_image = image(125,300,125,75,4,1,0.0,0xFF,0xFF,0xFF,0xFF,24);
    move_button.points.push_back(point(580,10));

    image_bundle reset_button = image_bundle();
    reset_button.m_image = image(125,300,125,75,4,1,0.0,0xFF,0xFF,0xFF,0xFF,24);
    reset_button.points.push_back(point(720,10));

    text_bundle title_text = text_bundle();
    title_text.m_text = text("Shrimpy Revenge",0xFF,0xFF,0xFF,0);

    text_bundle start_text = text_bundle();
    start_text.m_text = text("Start",0xFF,0xFF,0xFF,1);

    text_bundle red_text = text_bundle();
    red_text.m_text = text("Red x0",0xFF,0xFF,0xFF,0);

    text_bundle yellow_text = text_bundle();
    yellow_text.m_text = text("Yellow x0",0xFF,0xFF,0xFF,1);

    text_bundle green_text = text_bundle();
    green_text.m_text = text("Green x0",0xFF,0xFF,0xFF,2);

    text_bundle purple_text = text_bundle();
    purple_text.m_text = text("Purple x0",0xFF,0xFF,0xFF,3);

    text_bundle end_text = text_bundle();
    end_text.m_text = text("Thanks for playing!",0xFF,0xFF,0xFF,0);

    button_bundle start_event = button_bundle();
    start_event.m_button = button(1);
    start_event.rectangles.push_back({340,190,340,210});

    button_bundle red_event = button_bundle();
    red_event.m_button = button(2);
    red_event.rectangles.push_back({20,10,125,75});

    button_bundle yellow_event = button_bundle();
    yellow_event.m_button = button(3);
    yellow_event.rectangles.push_back({140,10,125,75});

    button_bundle green_event = button_bundle();
    green_event.m_button = button(4);
    green_event.rectangles.push_back({300,10,125,75});

    button_bundle purple_event = button_bundle();
    purple_event.m_button = button(5);
    purple_event.rectangles.push_back({440,10,125,75});

    button_bundle move_event = button_bundle();
    move_event.m_button = button(6);
    move_event.rectangles.push_back({580,10,125,75});

    button_bundle reset_event = button_bundle();
    reset_event.m_button = button(7);
    reset_event.rectangles.push_back({720,10,125,75});

    button_bundle bridge_placement = button_bundle();
    bridge_placement.m_button = button(8);
    bridge_placement.rectangles.push_back({0,0,SCREEN_WIDTH,SCREEN_HEIGHT*4/5});

    sound button_sound = sound(1);
    sound overbutton_sound = sound(2);

    //LOAD INTERFACES BASED ON ROOM NUMBER
    //
    switch (room_number){
    case ROOM_ONE:
        interfaces.push_back(game_interface(0,0,SCREEN_WIDTH,SCREEN_HEIGHT));

        interfaces[0].new_image(shrimp_bg);
        interfaces[0].new_image(start_button);

        interfaces[0].new_text(title_text);
        interfaces[0].new_text(start_text);

        interfaces[0].new_button(start_event);

        interfaces[0].new_sound(button_sound);
        interfaces[0].new_sound(overbutton_sound);

        interfaces[0].load_image(0,"images/nongame_screen.png");
        interfaces[0].load_image(1,"images/start_button.png");

        interfaces[0].load_sound(0,"sounds/button_click.wav");
        interfaces[0].load_sound(1,"sounds/button_reboun.wav");
    break;
    case ROOM_TWO:
        interfaces.push_back(game_interface(0,0,SCREEN_WIDTH,SCREEN_HEIGHT/5,SCREEN_WIDTH*6/5,SCREEN_HEIGHT/5));
        interfaces.push_back(game_interface(0,SCREEN_HEIGHT/5,SCREEN_WIDTH,SCREEN_HEIGHT*4/5));

        interfaces[0].new_image(ui_bg);
        interfaces[0].new_image(red_button);
        interfaces[0].new_image(yellow_button);
        interfaces[0].new_image(green_button);
        interfaces[0].new_image(purple_button);
        interfaces[0].new_image(move_button);
        interfaces[0].new_image(reset_button);

        interfaces[0].new_button(red_event);
        interfaces[0].new_button(yellow_event);
        interfaces[0].new_button(green_event);
        interfaces[0].new_button(purple_event);
        interfaces[0].new_button(move_event);
        interfaces[0].new_button(reset_event);

        interfaces[0].new_text(red_text);
        interfaces[0].new_text(yellow_text);
        interfaces[0].new_text(green_text);
        interfaces[0].new_text(purple_text);

        interfaces[0].new_sound(button_sound);
        interfaces[0].new_sound(overbutton_sound);

        interfaces[1].new_image(game_bg);
        interfaces[1].new_image(game_tile);
        interfaces[1].new_image(empty_tile);
        interfaces[1].new_image(bad_tile);
        interfaces[1].new_image(destination_tile);
        interfaces[1].new_image(crab);
        interfaces[1].new_image(red_bridge);
        interfaces[1].new_image(yellow_bridge);
        interfaces[1].new_image(green_bridge);
        interfaces[1].new_image(purple_bridge);
        interfaces[1].new_image(shrimp);

        interfaces[1].new_button(bridge_placement);

        interfaces[0].load_image(0,"images/game_tool_bar.png");
        interfaces[0].load_image(1,"images/button_image_1.png");
        interfaces[0].load_image(2,"images/button_image_2.png");
        interfaces[0].load_image(3,"images/button_image_1.png");
        interfaces[0].load_image(4,"images/button_image_2.png");
        interfaces[0].load_image(5,"images/button_image_1.png");
        interfaces[0].load_image(6,"images/button_image_2.png");

        interfaces[0].load_sound(0,"sounds/button_click.wav");
        interfaces[0].load_sound(1,"sounds/button_reboun.wav");

        interfaces[1].load_image(0,"images/game_screen.png");
        interfaces[1].load_image(1,"images/rock_tile.png");
        interfaces[1].load_image(2,"images/green_slot.png");
        interfaces[1].load_image(3,"images/bad_rock_tile.png");
        interfaces[1].load_image(4,"images/destination_rock_tile.png");
        interfaces[1].load_image(5,"images/crab.png");
        interfaces[1].load_image(6,"images/red_tile.png");
        interfaces[1].load_image(7,"images/yellow_tile.png");
        interfaces[1].load_image(8,"images/green_tile.png");
        interfaces[1].load_image(9,"images/purple_tile.png");
        interfaces[1].load_image(10,"images/shrimp_complete.png");
    break;
    case ROOM_THREE:
        interfaces.push_back(game_interface(0,0,SCREEN_WIDTH,SCREEN_HEIGHT));

        interfaces[0].new_image(shrimp_bg);
        interfaces[0].new_image(start_button);

        interfaces[0].new_text(end_text);

        interfaces[0].new_button(start_event);

        interfaces[0].new_sound(button_sound);
        interfaces[0].new_sound(overbutton_sound);

        interfaces[0].load_image(0,"images/nongame_screen.png");
        interfaces[0].load_image(1,"images/start_button.png");

        interfaces[0].load_sound(0,"sounds/button_click.wav");
        interfaces[0].load_sound(1,"sounds/button_reboun.wav");
    break;
    }

    return room_flag;
};

//REMOVING MEDIA OF ROOM (FOR END OF PROGRAM)
//
void room::clear_room(){
    interfaces.clear();
    game_timers.clear();
    file_readers.clear();
};

//ACTIVATING A ROOM
//
void room::activate_room(int room_number){
    is_active = true;

    //ACTIVATING INTERFACES
    //
    for (int i = 0; i < int(interfaces.size()); i++)
        interfaces[i].set_active(true);

    //ACTIVATING CERTAIN ROOM ELEMENTS
    //
    switch(room_number){
        case ROOM_ONE:
            interfaces[0].set_listening(true);

            interfaces[0].set_image_active(0,true);
            interfaces[0].set_image_active(1,true);

            interfaces[0].set_button_active(0,true);
        break;
        case ROOM_TWO:
            interfaces[0].set_listening(true);
            interfaces[1].set_listening(true);

            interfaces[0].set_image_active(0,true);
            interfaces[0].set_image_active(1,true);
            interfaces[0].set_image_active(2,true);
            interfaces[0].set_image_active(3,true);
            interfaces[0].set_image_active(4,true);
            interfaces[0].set_image_active(5,true);
            interfaces[0].set_image_active(6,true);

            interfaces[1].set_image_active(0,true);
            interfaces[1].set_image_active(1,true);
            interfaces[1].set_image_active(2,true);
            interfaces[1].set_image_active(3,true);
            interfaces[1].set_image_active(4,true);
            interfaces[1].set_image_active(5,true);
            interfaces[1].set_image_active(6,true);
            interfaces[1].set_image_active(7,true);
            interfaces[1].set_image_active(8,true);
            interfaces[1].set_image_active(9,true);
            interfaces[1].set_image_active(10,true);
        break;
        case ROOM_THREE:
            interfaces[0].set_listening(true);

            interfaces[0].set_image_active(0,true);
            interfaces[0].set_image_active(1,true);

            interfaces[0].set_button_active(0,true);
        break;
    }
}

//DEACTIVATING A ROOM
//
void room::deactivate_room(int room_number){
    //DEACTIVATING INTERFACES
    //
    int i, j = int(interfaces.size());
    is_active = false;

    for (i = 0; i < j; i++){
        interfaces[i].set_all_inactive();
    }

    //STOPPING TIMERS
    //
    j = int(game_timers.size());

    for (i = 0; i < j; i++)
        game_timers[i].stop();

    //DEACTIVATING CERTAIN ROOM ELEMENTS
    //
    switch(room_number){
    case ROOM_ONE:

    break;
    case ROOM_TWO:

    break;
        case ROOM_THREE:

    break;
    }
}

//
int* room::event_listen(SDL_Event& e){
    //IN CASE OF ANY WINDOW FEATURES CHANGING
    //
    window.handle_event(e.type,e.window.event,e.window.data1,e.window.data2);
    //GETTING MOUSE POSITION
    //
    int x1,y1, interface_length;
    SDL_GetMouseState(&x1,&y1);
    interface_length = int(interfaces.size());
    //ARRAY OF INTERFACE ACTIVITIES
    //
    int* activities = new int[interface_length];

    for (int i = 0; i < interface_length; i++){
        activities[i] = interfaces[i].touch_event(e.type,x1,y1);
        //std::cout << activities[i] << " ";
    }
    //std::cout << " " << std::endl;

    return activities;
};

//UPDATING ROOM (BASED ON RUNTIME)
//
void room::update(Uint32 ticks){
    //CHECK BEFOREHAND IF ROOM REQUIRES RUNTIME

    //CHECKING TICKS
    //
    std::cout << "Ticks given: " << ticks << std::endl;

    //UPDATE META-VARIABLES FIRST
    //


    //UPDATE KEY VARIABLES
    //


    //UPDATE INTERFACES
    //


    //CLOSING PROCEDURES (IF NEEDED)
    //

}

//RENDERING ROOM AFTER UPDATE
//
void room::render(){
    //INITIAL PROCEDURES (IF ANY)
    //
    SDL_Rect* test_fill;
    //REST OF RENDERING DONE IN INTERFACES
    //
    for (int i = int(interfaces.size())-1; i > -1; i--){
        test_fill = interfaces[i].get_viewport();

       // THIS IS FOR SEEING IF VIEWPORTS ARE BEING PLACED PROPERLY

        SDL_SetRenderDrawColor(renderer,255-i*30,255-i*30,255-i*30,255);

        SDL_RenderSetViewport(renderer,test_fill);
        SDL_RenderFillRect(renderer,test_fill);
        interfaces[i].render();
    }

    //CLOSING PROCEDURES (IF NEEDED)
    //

}

