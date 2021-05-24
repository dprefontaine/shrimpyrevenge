#include <z_media/images.h>

image::~image(){
    wipe();
    color_and_transparency.~SDL_Color();
    current_clip.~SDL_Rect();
}

void image::wipe(){
    if (texture != NULL)
        SDL_DestroyTexture(texture);
}

bool image::load_image(std::string image_path){
    wipe();
    //Loading a surface first
    //
    SDL_Surface* first_image = IMG_Load(image_path.c_str());

    if (first_image == NULL){
        std::cout << "Failed to load image: " << IMG_GetError() << std::endl;
    } else {
        //(0,255,0) IS INVISIBLE
        //
        SDL_SetColorKey(first_image,SDL_TRUE,SDL_MapRGB(first_image->format,0x00,0xFF,0xFF));
        //
        texture = SDL_CreateTextureFromSurface(renderer,first_image);

        //CLEARING IMAGES AND IMPLEMENTING TEXTURE
        //
        SDL_FreeSurface(first_image);
    }

    if (texture == NULL){
        std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
    } else {
        SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);
        SDL_SetTextureColorMod(texture,color_and_transparency.r,color_and_transparency.g,color_and_transparency.b);
    }

    return (!(texture == NULL));
}

void image::render(int x,int y){
    //rectangle spot of rendering
    //
    SDL_Rect render_spot = {x,y,x_size,y_size};
    //
    render_spot.w = current_clip.w;
    render_spot.h = current_clip.h;
    //printing rectangle dimensions
    //
    /*
    std::cout << "Current clip x: " << image::current_clip.x << ", Current clip y: " << image::current_clip.y << ", Current clip width: " << image::current_clip.w << ", Current clip height " << image::current_clip.h << std::endl;
    std::cout << "Render spot x: " << render_spot.x << ", Render spot y: " << render_spot.y << ", Render spot width: " << render_spot.w << ", Render spot height " << render_spot.h << std::endl;
    std::cout << image::texture << std::endl;
    */
    //
    //
    if (SDL_RenderCopy(renderer,texture,&current_clip,&render_spot) < 0){
        std::cout << "Failed to render image: " << IMG_GetError() << std::endl;
    }
}

void image::set_blend_mode(SDL_BlendMode blend_mode){
    SDL_SetTextureBlendMode(texture,blend_mode);
}

int image::get_x_size(){
    return x_size;
}

void image::set_x_size(int new_x_size){
    x_size = new_x_size;
}

int image::get_y_size(){
    return y_size;
}

void image::set_y_size(int new_y_size){
    y_size = new_y_size;
}

int image::get_x_clip(){
    return x_clip;
}

void image::set_x_clip(int new_x_clip){
    x_clip = new_x_clip;
}

int image::get_y_clip(){
    return y_clip;
}

void image::set_y_clip(int new_y_clip){
    y_clip = new_y_clip;
}

int image::get_state(){
    return current_state;
}
void image::set_state(int new_state){
    current_state = new_state;
}

int image::get_frame(){
    return current_frame;
}
void image::set_frame(int new_frame){
    current_frame = new_frame;
}

bool image::get_active(){
    return is_active;
}

void image::set_active(bool new_active){
    is_active = new_active;
}

double image::get_orientation(){
    return image_orientation;
}

void image::set_orientation(double new_orientation){
    image_orientation = new_orientation;
}

Uint8 image::get_red(){
    return color_and_transparency.r;
}

void image::set_red(Uint8 new_red){
    color_and_transparency.r = new_red;
    SDL_SetTextureColorMod(texture,color_and_transparency.r,color_and_transparency.g,color_and_transparency.b);
}

Uint8 image::get_green(){
    return color_and_transparency.g;
}

void image::set_green(Uint8 new_green){
    color_and_transparency.g = new_green;
    SDL_SetTextureColorMod(texture,color_and_transparency.r,color_and_transparency.g,color_and_transparency.b);
}

Uint8 image::get_blue(){
    return color_and_transparency.b;
}

void image::set_blue(Uint8 new_blue){
    color_and_transparency.b = new_blue;
    SDL_SetTextureColorMod(texture,color_and_transparency.r,color_and_transparency.g,color_and_transparency.b);
}

Uint8 image::get_transparency(){
    return color_and_transparency.a;
}

void image::set_transparency(Uint8 new_transparency){
    color_and_transparency.a = new_transparency;
    SDL_SetTextureAlphaMod(texture,color_and_transparency.a);
}

void image::update_clip(){
    //Modifying old clip
    //
    current_clip.x = ((current_frame-1)*x_clip);
    current_clip.y = ((current_state-1)*y_clip);
    current_clip.w = x_clip;
    current_clip.h = y_clip;
}

int image::get_element_ID(){
    return element_ID;
}

void image::set_element_ID(int new_element_ID){
    element_ID = new_element_ID;
}

int image::compare_element_ID(image image_obs){
    return element_ID - image_obs.get_element_ID();
}

int image::compare_to(image image_obs){
    int compare_num;

    if ((compare_num = compare_element_ID(image_obs)) == 0)
        if ((compare_num = (x_clip - image_obs.get_x_clip())) == 0)
            return y_clip - image_obs.get_y_clip();
        else
            return compare_num;
    else
        return compare_num;
}
