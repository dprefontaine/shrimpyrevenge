#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include "../z_media.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern SDL_Renderer* renderer;

class m_window{
public:
    //CONSTRUCTOR
    //
    m_window();
    //DESTRUCTOR
    //
    ~m_window();
    //INITIATION
    //
    bool init(std::string window_name = "SDL_PRACTICE_2");
    //CREATE RENDERER
    //
    SDL_Renderer* create_renderer();
    //
    //
    void handle_event(Uint32 e_type, Uint8 e_event, Sint32 data_1, Sint32 data_2);
    //DELOCATOR
    //
    void free();
    //FULL SCREEN MANAGER
    //
    void fullscreen_switch();
    //SIZE ACCESSOR
    //
    int get_x_size();
    int get_y_size();
    //LISTENER ACCESSORS
    //
    bool is_mouse_focus();
    bool is_keyboard_focus();
    //DETAIL ACCESSOR
    //
    bool is_minimized();

private:
    //Window
    //
    SDL_Window* main_window;
    //Dimensions
    //
    int x_size,y_size;
    //Listeners
    //
    bool mouse_focus;
    bool keyboard_focus;
    //Window details
    //
    bool fullscreen;
    bool minimized;
};

#endif // WINDOW_H_INCLUDED
