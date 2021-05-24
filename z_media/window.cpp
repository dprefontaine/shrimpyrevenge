#include <z_media/window.h>

m_window::m_window(){
    main_window = NULL;
    x_size = y_size = 0;
    fullscreen = minimized = keyboard_focus = mouse_focus = false;
}

m_window::~m_window(){

}

bool m_window::init(std::string window_name){
    bool window_init_flag = true;

    main_window = SDL_CreateWindow(window_name.c_str(),SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);

    if (main_window == NULL){
        std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
        window_init_flag = false;
    } else {
        x_size = SCREEN_WIDTH;
        y_size = SCREEN_HEIGHT;
        mouse_focus = true;
        keyboard_focus = true;
    }

    return window_init_flag;
}

SDL_Renderer* m_window::create_renderer(){
    return SDL_CreateRenderer(main_window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void m_window::free(){
    SDL_DestroyWindow(main_window);
}

void m_window::handle_event(Uint32 e_type, Uint8 e_event, Sint32 data_1, Sint32 data_2){
    //Event occur
    //
    if (e_type == SDL_WINDOWEVENT){
        switch (e_event){
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                x_size = data_1;
                y_size = data_2;
            break;
            case SDL_WINDOWEVENT_EXPOSED:
                SDL_RenderPresent(renderer);
            break;
            case SDL_WINDOWEVENT_ENTER:
                mouse_focus = true;
            break;
            case SDL_WINDOWEVENT_LEAVE:
                mouse_focus = false;
            break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                keyboard_focus = true;
            break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                keyboard_focus = false;
            break;
            case SDL_WINDOWEVENT_MINIMIZED:
                minimized = true;
            break;
            case SDL_WINDOWEVENT_MAXIMIZED:
                minimized = false;
            break;
            case SDL_WINDOWEVENT_RESTORED:
                minimized = false;
            break;
        }
    }
}

void m_window::fullscreen_switch(){
    //MANAGING FULLSCREEN
    //
    if (fullscreen){
        SDL_SetWindowFullscreen(main_window,SDL_FALSE);
        fullscreen = false;
    } else {
        SDL_SetWindowFullscreen(main_window,SDL_TRUE);
        fullscreen = true;
        minimized = false;
    }
}

int m_window::get_x_size(){
    return x_size;
}

int m_window::get_y_size(){
    return y_size;
}

bool m_window::is_mouse_focus(){
    return mouse_focus;
}

bool m_window::is_keyboard_focus(){
    return keyboard_focus;
}

bool m_window::is_minimized(){
    return minimized;
}
