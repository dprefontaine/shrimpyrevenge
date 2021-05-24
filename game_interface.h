#ifndef GAME_INTERFACE_H_INCLUDED
#define GAME_INTERFACE_H_INCLUDED

#include "z_media.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern m_window window;
extern SDL_Renderer* renderer;

class game_interface{
public:
    //CONSTRUCTOR
    //
    //extended (bound not set to viewport)
    game_interface(int vp_x,int vp_y,int vp_w,int vp_h, int x_bound, int y_bound){
        viewport.x = vp_x;
        viewport.y = vp_y;
        viewport.w = vp_w;
        viewport.h = vp_h;

        actual_viewport.x = 0;
        actual_viewport.y = 0;
        actual_viewport.w = vp_x + vp_w;
        actual_viewport.h = vp_y + vp_h;

        full_interface_size = point(x_bound, y_bound);
        game_camera = camera(-vp_x,-vp_y,vp_w+vp_x,vp_h+vp_y);

        is_active = false;
        is_listened = false;
    }
    //standard (bound is to the viewport size)
    game_interface(int vp_x = 0, int vp_y = 0, int vp_w = 1, int vp_h = 1) : game_interface(vp_x,vp_y,vp_w,vp_h,vp_w,vp_h){};
    //
    //DESTRUCTOR
    ~game_interface();
    //CLEARER
    //
    void clear_interface();
    //VIEWPORT MANAGER
    //
    SDL_Rect* get_viewport();
    //
    //RENDERING
    //
    void render();
    //
    ////EVENTS
    //
    int touch_event(Uint32 e_type, int x1, int y1);
    bool* hitbox_check(int element_ID_1 = 0, int element_ID_2 = 0);
    //
    ////BUTTON MANAGER
    //
    bool new_button(button_bundle new_button);
    bool update_button(int index = 0, int new_state = 0);
    bool move_button(int index = 0, int x_move = 0, int y_move = 0);
    bool set_button_active(int index = 0, bool active = false);
    int find_button_by_ID(int element_ID = 0);
    int find_button(button button_obs);
    button get_button(int index = 0);
    bool add_button_rectangle(int index = 0, SDL_Rect new_rect = {});
    bool remove_button_rectangle(int index = 0, SDL_Rect given_rect = {});
    bool clear_button(int index = 0);
    void sort_buttons();
    //
    ////EVENT CLUSTER MANAGER
    //
    bool new_cluster(event_cluster new_cluster);
    bool update_cluster_ID(int index = 0, int new_element_ID = 0);
    bool set_cluster_active(int index = 0, bool active = false);
    int find_cluster_by_ID(int element_ID = 0);
    int find_cluster(event_cluster cluster_obs);
    event_cluster get_cluster(int index = 0);
    bool move_cluster(int index = 0, int x_move = 0, int y_move = 0);
    bool add_cluster_rect(int index = 0, event_rectangle new_rect = event_rectangle());
    bool add_cluster_circ(int index = 0, event_circle new_circ = event_circle());
    bool remove_cluster_rect(int index = 0, event_rectangle given_rect = event_rectangle());
    bool remove_cluster_circ(int index = 0, event_circle given_circ = event_circle());
    bool clear_cluster(int index = 0);
    //
    ////IMAGE MANAGER
    //
    bool new_image(image_bundle n_image);
    bool load_image(int index = 0, std::string image_path = "");
    bool update_image(int index = 0, int state = 0, int frame = 0);
    bool set_image_active(int index = 0, bool active = false);
    int find_image_by_ID(int element_ID = 0);
    int find_image(image image_obs);
    image get_image(int index = 0);
    bool add_image_spot(int index = 0, point new_point = point());
    bool move_image_spot(int index = 0, point given_point = point(), int x_move = 0, int y_move = 0);
    bool remove_image_spot(int index = 0, point given_point = point());
    bool clear_image(int index = 0);
    //
    ////SHAPE MANAGER
    //
    bool new_shape(shape_bundle n_shape);
    bool set_shape_active(int index = 0, bool active = false);
    int find_shape_by_ID(int element_ID = 0);
    int find_shape(shape obs_shape);
    shape get_shape(int index = 0);
    bool add_shape_spot(int index = 0, point new_point = point());
    bool move_shape_spot(int index = 0, point given_point = point(), int x_move = 0, int y_move = 0);
    bool remove_shape_spot(int index = 0, point given_point = point());
    bool clear_shape(int index = 0);
    //
    ////TEXT MANAGER
    //
    bool new_text(text_bundle n_text);
    bool load_text(int index = 0, int font = 0, int font_scale = 1);
    bool set_text_content(int index = 0, std::string text_content = "");
    bool set_text_color(int index = 0, SDL_Color text_color = {0,0,0});
    bool set_text_active(int index = 0, bool active = false);
    int find_text_by_ID(int element_ID = 0);
    int find_text(text text_obs);
    text get_text(int index = 0);
    bool add_text_spot(int index = 0, point new_point = point());
    bool move_text_spot(int index = 0, point given_point = point(), int x_move = 0, int y_move = 0);
    bool remove_text_spot(int index = 0, point given_point = point());
    bool clear_text(int index = 0);
    //
    ////SOUND MANAGER
    //
    bool new_sound(sound n_sound);
    bool load_sound(int index = 0, std::string sound_path = "");
    bool set_sound_active(int index, bool active = false);
    bool play_sound(int index = 0);
    int find_sound_by_ID(int element_ID = 0);
    sound get_sound(int index = 0);
    bool clear_sound(int index = 0);
    //
    ////CAMERA MANAGER (offset to other objects more implied)
    //
    void updating_camera(int x_move = 0, int y_move = 0);
    //
    ////ACTIVE AND LISTENING MANAGER
    //
    bool get_active();
    void set_active(bool active = false);
    void set_all_inactive();
    //
    bool get_listening();
    void set_listening(bool listening = false);

private:
    //GAME BUTTONS (FOR TOUCH EVENT) AND OTHER EVENT STUFF
    //
    std::vector<button_bundle> game_buttons = {};
    std::vector<event_cluster> game_hitboxes = {};
    //MEDIA BINS
    //
    std::vector<image_bundle> game_images = {};
    std::vector<shape_bundle> game_shapes = {};
    std::vector<text_bundle> game_text = {};
    std::vector<sound> game_sounds = {};
    //MATH BINS AND STUFF
    //
    camera game_camera;
    point full_interface_size;
    //IS ACTIVE, LISTENED, OR NOT
    //
    bool is_active;
    bool is_listened;
    //VIEWING WINDOW OF INTERFACE
    //
    SDL_Rect viewport;
    SDL_Rect actual_viewport;
};

#endif // GAME_INTERFACE_H_INCLUDED
