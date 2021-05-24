#include <game_interface.h>

//DESTRUCTOR

game_interface::~game_interface(){
    clear_interface();
    game_buttons.clear();
    game_hitboxes.clear();

    game_camera.~camera();
    game_hitboxes.~vector();
    full_interface_size.~point();
    game_buttons.~vector();
    game_images.~vector();
    game_shapes.~vector();
    game_sounds.~vector();
    game_text.~vector();
}

void game_interface::clear_interface(){
    is_active = false;
    is_listened = false;

    //CLEAR MEDIA STUFF
    game_images.clear();
    game_shapes.clear();
    game_sounds.clear();
    game_text.clear();
}

//VIEWPORT MANAGER

SDL_Rect* game_interface::get_viewport(){
    return &actual_viewport;
}

void game_interface::render(){
    //RENDERING IMAGES FIRST (POSITION RELATIVE TO CAMERA)
    int length = int(game_images.size()), i;

    for (i = 0; i < length; i++)
        game_images[i].render_bundle(game_camera.get_x_pos(),game_camera.get_y_pos(),game_camera.get_x_size(),game_camera.get_y_size());
    //RENDERING SHAPES (POSITION RELATIVE TO CAMERA)

    length = int(game_shapes.size());

    for (i = 0; i < length; i++)
        game_shapes[i].render_bundle(game_camera.get_x_pos(),game_camera.get_y_pos(),game_camera.get_x_size(),game_camera.get_y_size());
    //RENDERING TEXT (POSITION RELATIVE TO CAMERA)

    length = int(game_text.size());

    for (i = 0; i < length; i++)
        game_text[i].render_bundle(game_camera.get_x_pos(),game_camera.get_y_pos(),game_camera.get_x_size(),game_camera.get_y_size());
}

//TOUCH EVENT MANAGER

int game_interface::touch_event(Uint32 e_type, int x1, int y1){
    //INITIALIZING THIS FIRST IN CASE OF VOID CASES
    //
    //J REPRESENTS A PARTICULAR NODE EVENT RETURNED TO THE MAIN PROGRAM
    //
    int j = -1;

    //TO SHOW THE MOUSE IS OVER A VIEWPORT
    //
    if (x1 > viewport.x && x1 < viewport.x + viewport.w && y1 > viewport.y && y1 < viewport.y + viewport.h){
        j = 0;
    }

    if (is_active && is_listened && j == 0 &&
        (e_type == SDL_MOUSEMOTION || e_type == SDL_MOUSEBUTTONDOWN || e_type == SDL_MOUSEBUTTONUP) &&
        window.is_mouse_focus() && !(window.is_minimized())){
        //GET MOUSE POSITION
        //
        int x2,y2,h,w,k;
        bool over_button = false;
        k = game_buttons.size();
        //CYCLE THROUGH BUTTON STACK AND EVALUATE ALL BUTTON RECTANGLES
        //
        //ALSO CONSIDER THE OFFSET OF THE VIEWPORT (OR THE STARTING CORNER COORDINATES OF THE VIEWPORT)
        //
        //USING WHILE SO THAT NOT ALL VIEWPORTS HAVE TO BE CYCLED IF REACHED
        //
        //THE LOOP SHOULD BREAK ONCE A BUTTON IS REACHED
        //
        while (!(over_button) && j < k){
            //GET ALL THE RECTANGLES WITHIN A BUTTON BUNDLE
            //
            int l,rect_length = int(game_buttons[j].rectangles.size());

            //(this is really ugly)
            for (l = 0; l < rect_length; l++){
                x2 = game_buttons[j].rectangles[l].x + viewport.x;
                y2 = game_buttons[j].rectangles[l].y + viewport.y;
                w = game_buttons[j].rectangles[l].w;
                h = game_buttons[j].rectangles[l].h;
                //
                //CHECKING X AXIS FIRST
                if (x1 > x2 && x1 < (x2 + w))
                //
                //CHECKING Y AXIS
                    if (y1 > y2 && y1 < (y2 + h))
                        over_button = true;
                    //MOVE ONTO NEXT ELEMENT
                    //
                    else
                        j++;
                //MOVE ONTO NEXT ELEMENT
                //
                else
                    j++;
            }
        }
        //
        //IF REACHED THE END OF THE LIST
        if (j == k)
            j = 0;
        else {
            //IF CONDITION FOR ANY OF THE BUTTONS IS FULFILLED, RETURN A VALUE RELATED TO ITS NODE
            //
            //NODE = (BUTTON STACK)*4 + some number
            //
            //WARNING: PROBABLY WILL HAVE TO MANUALLY PROGRAM RENDERING AND BASE EVENTS FOR EACH BUTTON CONDITION
            //
            switch (e_type){
            case SDL_MOUSEBUTTONUP:
                update_button(j,1);
                j = j*4 + 1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                update_button(j,2);
                j = j*4 + 2;
                break;
            case SDL_MOUSEMOTION:
                update_button(j,3);
                j = j*4 + 3;
                break;
            }
        }
    }

    return j;
}

//EVENT AREA CHECKER

bool* game_interface::hitbox_check(int element_ID_1,int element_ID_2){
    int hitbox_start = 0, hitbox_length = int(game_hitboxes.size());

    //GET THE FIRST OBJECT WITH ELEMENT ID 1 IN THE LIST (TO SHORTEN THE TABLE AND THE SEARCH)
    //
    while (game_hitboxes[hitbox_start].element_ID != element_ID_1 && hitbox_start < hitbox_length)
        hitbox_start++;
    //GET THE LAST OBJECT WITH ELEMENT ID 1 IN THE LIST (TO SHORTEN THE TABLE AND THE SEARCH)
    //
    while (game_hitboxes[hitbox_length-1].element_ID != element_ID_1 && hitbox_length > hitbox_start)
        hitbox_length--;

    //HITBOX ACTIVITIES TABLE
    //
    bool* hitbox_activities = new bool[hitbox_length];

    for (;hitbox_start < hitbox_length; hitbox_start++)
        if (game_hitboxes[hitbox_start].element_ID == element_ID_1)
            for (int j = hitbox_start; j < hitbox_length; j++)
                if (hitbox_activities[j] == element_ID_2)
                    hitbox_activities[hitbox_start] = game_hitboxes[hitbox_start].is_contact(game_hitboxes[j]);
                else
                    hitbox_activities[hitbox_start] = false;
        else
            hitbox_activities[hitbox_start] = false;

    return hitbox_activities;
};

//MEDIA BIN MANAGERS

bool game_interface::new_button(button_bundle new_rect){
    int push_diff = int(game_buttons.size());

    game_buttons.push_back(new_rect);

    push_diff = int(game_buttons.size()) - push_diff;

    return (push_diff == 1);
}

bool game_interface::update_button(int index, int new_state){
    bool update_flag = true;

    if (index < int(game_buttons.size()) && index > -1)
        game_buttons[index].m_button.set_state(new_state);

    return update_flag;
}

bool game_interface::move_button(int index, int x_move, int y_move){
    if (index < 0 || index > int(game_buttons.size() - 1))
        return false;
    else {
        game_buttons[index].move_rectangles(x_move,y_move);
        return true;
    }
}

bool game_interface::set_button_active(int index, bool active){
    if (index < 0 || index > int(game_buttons.size() - 1))
        return false;
    else {
        game_buttons[index].m_button.set_active(active);
        return true;
    }
}

int game_interface::find_button_by_ID(int element_ID){
    int i = 0;

    while (i < int(game_buttons.size()))
        if (game_buttons[i].m_button.get_element_ID() == element_ID)
            return i;
        else
            i++;

    return -1;
}

int game_interface::find_button(button button_obs){
    int i = 0;

    while (i < int(game_buttons.size()))
        if (game_buttons[i].m_button.compare_to(button_obs) == 0)
            return i;
        else
            i++;

    return -1;
}

button game_interface::get_button(int index){
    if (index < 0 || index > int(game_buttons.size() - 1)){
        button null_button = button();
        return null_button;
    } else
        return game_buttons[index].m_button;
}

bool game_interface::add_button_rectangle(int index, SDL_Rect new_rect){
    if (index < 0 || index > int(game_buttons.size() - 1))
        return false;
    else {
        game_buttons[index].rectangles.push_back(new_rect);
        return true;
    }
}

bool game_interface::remove_button_rectangle(int index, SDL_Rect given_rect){
    if (index < 0 || index > int(game_buttons.size() - 1))
        return false;
    else {
        game_buttons[index].rectangles.erase(game_buttons[index].rectangles.begin() + index);
        return true;
    }
}

bool game_interface::clear_button(int index){
    if (index < 0 || index > int(game_buttons.size()-1))
        return false;
    else {
        game_buttons.erase(game_buttons.begin() + index);
        return true;
    }
}

//EVENT CLUSTER

bool game_interface::new_cluster(event_cluster new_cluster){
    int push_diff = int(game_hitboxes.size());

    game_hitboxes.push_back(new_cluster);

    push_diff = int(game_hitboxes.size()) - push_diff;

    return (push_diff == 1);
}

bool game_interface::update_cluster_ID(int index, int new_element_ID){
    if (index < 0 || index > int(game_hitboxes.size()))
        return false;
    else {
        game_hitboxes[index].element_ID = new_element_ID;
        return true;
    }
}

bool game_interface::set_cluster_active(int index, bool active){
    if (index < 0 || index > int(game_hitboxes.size()))
        return false;
    else {
        game_hitboxes[index].is_active = active;
        return true;
    }
}

int game_interface::find_cluster_by_ID(int element_ID){
    int i = 0;

    while (i < int(game_hitboxes.size()))
        if (game_hitboxes[i].element_ID == element_ID)
            return i;
        else
            i++;

    return -1;
}

int game_interface::find_cluster(event_cluster cluster_obs){
    int i = 0;

    while (i < int(game_hitboxes.size()))
        if (game_hitboxes[i].compare_to(cluster_obs) == 0)
            return i;
        else
            i++;

    return -1;
}

event_cluster game_interface::get_cluster(int index){
    if (index < 0 || index > int(game_hitboxes.size())){
        event_cluster null_cluster = event_cluster();
        return null_cluster;
    } else
        return game_hitboxes[index];
}

bool game_interface::move_cluster(int index, int x_move, int y_move){
    if (index < 0 || index > int(game_hitboxes.size()))
        return false;
    else {
        game_hitboxes[index].move_clusters(x_move,y_move);
        return true;
    }
}

bool game_interface::add_cluster_rect(int index, event_rectangle new_rect){
    if (index < 0 || index > int(game_hitboxes.size()))
        return false;
    else {
        game_hitboxes[index].event_rectangles.push_back(new_rect);
        return true;
    }
}

bool game_interface::add_cluster_circ(int index, event_circle new_circ){
    if (index < 0 || index > int(game_hitboxes.size() - 1))
        return false;
    else {
        game_hitboxes[index].event_circles.push_back(new_circ);
        return true;
    }
}

bool game_interface::remove_cluster_rect(int index, event_rectangle given_rect){
    if (index < 0 || index > int(game_hitboxes.size() - 1))
        return false;
    else {
        int rect_search = 0;

        while (rect_search < int(game_hitboxes.size()))
            if (game_hitboxes[index].event_rectangles[rect_search].compare_to(given_rect) == 0){
                game_hitboxes[index].event_rectangles.erase(game_hitboxes[index].event_rectangles.begin() + rect_search);
                return true;
            } else
                rect_search++;

        return false;
    }
}

bool game_interface::remove_cluster_circ(int index, event_circle given_circ){
    if (index < 0 || index > int(game_hitboxes.size() - 1))
        return false;
    else {
        int circ_search = 0;

        while (circ_search < int(game_hitboxes.size()))
            if (game_hitboxes[index].event_circles[circ_search].compare_to(given_circ) == 0){
                game_hitboxes[index].event_circles.erase(game_hitboxes[index].event_circles.begin() + circ_search);
                return true;
            } else
                circ_search++;

        return false;
    }
}

bool game_interface::clear_cluster(int index){
    if (index < 0 || index > int(game_hitboxes.size() - 1))
        return false;
    else {
        game_hitboxes.erase(game_hitboxes.begin() + index - 1);
        return true;
    }
}

//IMAGE MANAGERS

bool game_interface::new_image(image_bundle n_image){
    //BOOL IS BASED ON IF THE IMAGE STACK SIZE HAS INCREASED OR NOT
    //
    int push_diff = int(game_images.size());

    game_images.push_back(n_image);

    push_diff = int(game_images.size()) - push_diff;

    return (push_diff == 1);
}

bool game_interface::load_image(int index, std::string image_path){
    if (int(game_images.size()) > index && index > -1)
        return game_images[index].m_image.load_image(image_path);
    else {
        std::cout << "This index is not available!" << std::endl;
        return false;
    }
}

bool game_interface::update_image(int index, int state, int frame){
    //Check if index exists
    //
    if (int(game_images.size()) > index && index > -1) {
        game_images[index].m_image.set_state(state);
        game_images[index].m_image.set_frame(frame);
        game_images[index].m_image.update_clip();
        return true;
    } else {
        std::cout << "This index is not available!" << std::endl;
        return false;
    }
}

bool game_interface::set_image_active(int index, bool active){
    //Check if index exists
    //
    if (int(game_images.size()) > index && index > -1) {
        game_images[index].m_image.set_active(active);
        return true;
    } else {
        std::cout << "This index is not available!" << std::endl;
        return false;
    }
}

int game_interface::find_image_by_ID(int element_ID){
    int i = 0;

    while (i < int(game_images.size()))
        if (game_images[i].m_image.get_element_ID() == element_ID)
            return i;
        else
            i++;

    return -1;
}

int game_interface::find_image(image image_obs){
    int i = 0;

    while (i < int(game_images.size()))
        if (game_images[i].m_image.compare_to(image_obs))
            return i;
        else
            i++;

    return i;
}

image game_interface::get_image(int index){
    //Check if index exists
    //
    if (int(game_images.size()) > index && index > -1) {
        return game_images[index].m_image;
    } else {
        std::cout << "This index is not available!" << std::endl;

        image null_image = image();
        return null_image;
    }
}

bool game_interface::add_image_spot(int index, point new_point){
    if (index < 0 || index > int(game_images.size()-1))
        return false;
    else {
        game_images[index].points.push_back(new_point);
        return true;
    }
}

bool game_interface::move_image_spot(int index, point given_point, int x_move, int y_move){
    if (index < 0 || index > int(game_images.size()-1))
        return false;
    else {
        //SEARCH FOR THE POINT
        //
        int point_search = game_images[index].search_point(given_point);

        if (point_search > -1){
            game_images[index].points[point_search].set_x(game_images[index].points[point_search].get_x()+x_move);
            game_images[index].points[point_search].set_y(game_images[index].points[point_search].get_y()+y_move);

            return true;
        } else
            return false;
    }
}

bool game_interface::remove_image_spot(int index, point given_point){
    if (index < 0 || index > int(game_images.size()-1))
        return false;
    else {
        //SEARCH FOR THE POINT
        //
        int point_search = game_images[index].search_point(given_point);

        if (point_search > -1){
            game_images[index].points.erase(game_images[index].points.begin() + point_search);
            return true;
        } else
            return false;
    }
}

bool game_interface::clear_image(int index){
    if (index < 0 || index > int(game_images.size()-1))
        return false;
    else {
        game_images.erase(game_images.begin() + index);
        return true;
    }
}

//SHAPE MANAGERS

bool game_interface::new_shape(shape_bundle n_shape){
    //CHECK FOR CHANGE IN SHAPE STACK SIZE
    //
    int stack_change = int(game_shapes.size());

    game_shapes.push_back(n_shape);

    stack_change = int(game_shapes.size()) - stack_change;

    return (stack_change == 1);
}

bool game_interface::set_shape_active(int index, bool active){
    //CHECK IF INDEX EXISTS
    //
    if (index < 0 || index > int(game_shapes.size()-1))
        return false;
    else {
        game_shapes[index].m_shape.set_active(active);
        return true;
    }
}

int game_interface::find_shape_by_ID(int element_ID){
    int i = 0;

    while (i < int(game_shapes.size()))
        if (game_shapes[i].m_shape.get_element_ID() == element_ID)
            return i;
        else
            i++;

    return -1;
}

int game_interface::find_shape(shape obs_shape){
    int i = 0;

    while (i < int(game_shapes.size()))
        if (game_shapes[i].m_shape.compare_to(obs_shape) == 0)
            return i;
        else
            i++;

    return i;
}

shape game_interface::get_shape(int index){
    //CHECK IF INDEX EXISTS
    //
    if (int(game_shapes.size()) > index && index > -1)
        return game_shapes[index].m_shape;
    else {
        shape null_shape = shape();

        return null_shape;
    }
}

bool game_interface::add_shape_spot(int index, point new_point){
    //CHECK IF INDEX EXISTS
    //
    if (int(game_shapes.size()) > index && index > -1){
        game_shapes[index].points.push_back(new_point);
        return true;
    } else {
        return false;
    }
}

bool game_interface::move_shape_spot(int index, point given_point, int x_move, int y_move){
    if (index < 0 || index > int(game_shapes.size()-1))
        return false;
    else {
        //SEARCH FOR THE POINT
        //
        int point_search = game_shapes[index].search_point(given_point);

        if (point_search > -1){
            game_shapes[index].points[point_search].set_x(game_shapes[index].points[point_search].get_x()+x_move);
            game_shapes[index].points[point_search].set_y(game_shapes[index].points[point_search].get_y()+y_move);

            return true;
        } else
            return false;
    }
}

bool game_interface::remove_shape_spot(int index, point given_point){
    //CHECK IF INDEX EXISTS
    //
    if (int(game_shapes.size()) > index && index > -1){
        //CHECK IF POINT EXISTS
        //
        int point_search = game_shapes[index].search_point(given_point);

        if (point_search > -1){
            game_shapes[index].points.erase(game_shapes[index].points.begin() + point_search - 1);
            return true;
        } else
            return false;
    } else {
        return false;
    }
}

bool game_interface::clear_shape(int index){
    //CHECK IF INDEX EXISTS
    //
    if (int(game_shapes.size()) > index && index > -1){
        game_shapes.erase(game_shapes.begin() + index - 1);
        return true;
    } else
        return false;
}

//TEXT MANAGERS

bool game_interface::new_text(text_bundle n_text){
    //BOOL IS BASED ON IF THE IMAGE STACK SIZE HAS INCREASED OR NOT
    //
    int push_diff = int(game_text.size());

    game_text.push_back(n_text);

    push_diff = int(game_text.size()) - push_diff;

    return (push_diff == 1);
}

bool game_interface::load_text(int index, int font, int font_scale){
    //Check if index exists
    //
    if (int(game_text.size()) > index && index > -1) {
        game_text[index].m_text.load_text(font,font_scale);
        return true;
    } else {
        std::cout << "This index is not available!" << std::endl;
        return false;
    }
}

bool game_interface::set_text_content(int index, std::string text_content){
    //Check if index exists
    //
    if (int(game_text.size()) > index && index > -1) {
        game_text[index].m_text.set_content(text_content);
        return true;
    } else {
        std::cout << "This index is not available!" << std::endl;
        return false;
    }
}

bool game_interface::set_text_color(int index, SDL_Color text_color){
    //Check if index exists
    //
    if (int(game_text.size()) > index && index > -1) {
        game_text[index].m_text.set_red(text_color.r);
        game_text[index].m_text.set_green(text_color.g);
        game_text[index].m_text.set_blue(text_color.b);
        game_text[index].m_text.set_alpha(text_color.a);
        return true;
    } else {
        std::cout << "This index is not available!" << std::endl;
        return false;
    }
}

bool game_interface::set_text_active(int index, bool active){
    //Check if index exists
    //
    if (int(game_text.size()) > index && index > -1) {
        game_text[index].m_text.set_active(active);
        return true;
    } else {
        std::cout << "This index is not available!" << std::endl;
        return false;
    }
}

int game_interface::find_text_by_ID(int element_ID){
    int i = 0;

    while (i < int(game_text.size()))
        if (game_text[i].m_text.get_element_ID() == element_ID)
            return i;
        else
            i++;

    return -1;
}

int game_interface::find_text(text text_obs){
    int i = 0;

    while (i < int(game_text.size()))
        if (game_text[i].m_text.compare_to(text_obs) == 0)
            return i;
        else
            i++;

    return -1;
}

text game_interface::get_text(int index){
    //Check if index exists
    //
    if (int(game_text.size()) > index && index > -1) {
        return game_text[index].m_text;
    } else {
        std::cout << "This index is not available!" << std::endl;

        text null_text = text();

        return null_text;
    }
}

bool game_interface::add_text_spot(int index, point new_point){
    if (index < 0 || int(game_text.size() - 1))
        return false;
    else {
        game_text[index].points.push_back(new_point);
        return true;
    }
}

bool game_interface::move_text_spot(int index, point given_point, int x_move, int y_move){
    if (index < 0 || index > int(game_text.size()-1))
        return false;
    else {
        //SEARCH FOR THE POINT
        //
        int point_search = game_text[index].search_point(given_point);

        if (point_search > -1){
            game_text[index].points[point_search].set_x(game_text[index].points[point_search].get_x()+x_move);
            game_text[index].points[point_search].set_y(game_text[index].points[point_search].get_y()+y_move);

            return true;
        } else
            return false;
    }
}

bool game_interface::remove_text_spot(int index, point given_point){
    if (index < 0 || index > int(game_text.size() - 1))
        return false;
    else {
        int text_search = game_text[index].search_point(given_point);

        if (text_search > -1){
            game_text[index].points.erase(game_text[index].points.begin() + text_search);
            return true;
        } else
            return false;
    }
}

bool game_interface::clear_text(int index){
    if (index < 0 || index > int(game_text.size() - 1))
        return false;
    else {
        game_text.erase(game_text.begin() + index);
        return true;
    }
}

//SOUND MANAGERS

bool game_interface::new_sound(sound n_sound){
    //BOOL IS BASED ON IF THE IMAGE STACK SIZE HAS INCREASED OR NOT
    //
    int push_diff = int(game_sounds.size());

    game_sounds.push_back(n_sound);

    push_diff = int(game_sounds.size()) - push_diff;

    return (push_diff == 1);
}

bool game_interface::load_sound(int index, std::string sound_path){
    //Check if index exists
    //
    if (int(game_sounds.size()) > index && index > -1) {
        return game_sounds[index].load_sound(sound_path);
    } else {
        std::cout << "This index is not available!" << std::endl;
        return false;
    }
}

bool game_interface::set_sound_active(int index, bool active) {
    //CHECK IF INDEX IS AVAILABLE
    //
    if (index > -1 && index < int(game_sounds.size())){
        game_sounds[index].set_active(active);
        return true;
    } else
        return false;
}

bool game_interface::play_sound(int index){
    //Check if index exists
    //
    if (int(game_sounds.size()) > index && index > -1) {
        game_sounds[index].play();
        return true;
    } else {
        std::cout << "This index is not available!" << std::endl;
        return false;
    }
}

int game_interface::find_sound_by_ID(int element_ID){
    int i = 0;

    while (i < int(game_sounds.size())){
        if (game_sounds[i].get_element_ID() == element_ID)
            return i;
        i++;
    }

    return -1;
}

sound game_interface::get_sound(int index){
    //Check if index exists
    //
    if (int(game_sounds.size()) > index && index > -1) {
        return game_sounds[index];
    } else {
        std::cout << "This index is not available!" << std::endl;
        return false;
    }
}

bool game_interface::clear_sound(int index){
    //Check if index exists
    //
    if (index < 0 || index > int(game_sounds.size()-1))
        return false;
    else {
        game_sounds.erase(game_sounds.begin() + index);
        return true;
    }
}

//CAMERA MANAGER

void game_interface::updating_camera(int x_move, int y_move){
    //SETTING INITIAL NEW POSITIONS
    //
    int new_x_pos = game_camera.get_x_pos() + x_move;
    int new_y_pos = game_camera.get_y_pos() + y_move;
    //TO CHECK WHETHER OR NOT THE SCREEN MOVED
    //
    bool button_move_flag = true;

    //CHECKING X BOUNDS
    //
    if (new_x_pos+game_camera.get_x_size() > full_interface_size.get_x()){
        new_x_pos = full_interface_size.get_x() - game_camera.get_x_size();
        button_move_flag = false;
    } else if (new_x_pos < -viewport.x) {
        new_x_pos = -viewport.x;
        button_move_flag = false;
    }
    //CHECKING Y BOUNDS
    //
    if (new_y_pos+game_camera.get_y_size() > full_interface_size.get_y()){
        new_y_pos = full_interface_size.get_y() - game_camera.get_y_size();
        button_move_flag = false;
    } else if (new_y_pos < -viewport.y) {
        new_y_pos = -viewport.y;
        button_move_flag = false;
    }

    //std::cout << "New camera x position: " << new_x_pos << std::endl;
    //std::cout << "New camera y position: " << new_y_pos << std::endl;

    game_camera.set_x_pos(new_x_pos);
    game_camera.set_y_pos(new_y_pos);

    //SETTING BUTTONS
    //
    if (button_move_flag)
        for (int i = 0; i < int(game_buttons.size()); i++)
            game_buttons[i].move_rectangles(-x_move,-y_move);
}

//ACTIVE AND LISTENING MANAGERS

bool game_interface::get_active(){
    return is_active;
}

void game_interface::set_active(bool active){
    is_active = active;
}

void game_interface::set_all_inactive(){
    int i;

    //DEACTIVATING EVENT STUFF

    //DEACTIVATING BUTTONS
    //
    for (i = 0; i < int(game_buttons.size()); i++)
        set_button_active(i,false);
    //DEACTIVATING HITBOXES
    //
    for (i = 0; i < int(game_hitboxes.size()); i++)
        set_cluster_active(i,false);

    //DEACTIVATING MEDIA

    //DEACTIVATING IMAGES
    //
    for (i = 0; i < int(game_images.size()); i++)
        set_image_active(i,false);
    //DEACTIVATING SHAPES
    //
    for (i = 0; i < int(game_shapes.size()); i++)
        set_shape_active(i,false);
    //DEACTIVATING TEXT
    //
    for (i = 0; i < int(game_text.size()); i++)
        set_text_active(i,false);
    //DEACTIVATING SOUNDS
    //
    for (i = 0; i < int(game_sounds.size()); i++)
        set_sound_active(i,false);

    std::cout << "All interface elements have been set inactive" << std::endl;

    is_active = false;
}

bool game_interface::get_listening(){
    return is_listened;
}

void game_interface::set_listening(bool listening){
    is_listened = listening;
}
