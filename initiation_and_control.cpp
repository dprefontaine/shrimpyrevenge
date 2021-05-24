#include <initiation_and_control.h>

//CODE OF INITIATION AND CLOSING PROCEDURES, AS WELL AS GENERAL CONTROL PROCEDURES DURING THE GAME
//

bool initialize(){
    //INITIATION FLAG
    bool init_flag = true;

    for (int i = 0; i < TOTAL_FONTS; i++)
        fonts[i] = NULL;

    //START BY INITIALIZING BASE SDL
    //
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0){
        std::cout << "Failed to initialize: " << SDL_GetError() << std::endl;
        init_flag = false;
    } else {
        //INITIALIZING WINDOW
        //
        if (!(window.init(SCREEN_NAME))){
            std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
            init_flag = false;
        } else {
            //INITIALIZE RENDERER AND OTHER ELEMENTS
            //
            renderer = window.create_renderer();

            if (renderer == NULL){
                std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
                init_flag = false;
            } else {
                SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,0xFF);
                SDL_RenderClear(renderer);
                //INITIALIZING IMAGE LIBRARY
                //
                int png_flag = IMG_INIT_PNG;

                if (!(IMG_Init(png_flag) & png_flag)){
                    std::cout << "Failed to load png images: " << IMG_GetError() << std::endl;
                }
            }
            //INITIALIZING TRUETYPEFONTS
            //
            if (TTF_Init() == -1){
                std::cout << "Failed to initialize TTF: " << TTF_GetError() << std::endl;
            } else {
                fonts[1] = TTF_OpenFont("fonts/ANDYFISH.ttf",64);
                fonts[2] = TTF_OpenFont("fonts/fishsausages.ttf",23);
            }
            //INITIALIZING MIXER
            //
            if (Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048) < 0){
                std::cout << "Failed to initiate sound mixer!" << Mix_GetError() << std::endl;
                init_flag = false;
            }

            SDL_EnableScreenSaver();
            SDL_StartTextInput();
        }
    }

    return init_flag;
}

void close(){
    //Clear window
    //
    std::cout << "Clearing window........";
    window.free();
    window.~m_window();
    std::cout << "successfully closed!" << std::endl;
    //Clear renderer
    //
    std::cout << "Clearing renderer........";
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    std::cout << "successfully closed!" << std::endl;
    ////ENDING SDL ACTIVITIES
    //
    std::cout << "Ending SDL activities........";
    SDL_DisableScreenSaver();
    SDL_StopTextInput();
    std::cout << " successfully closed!" << std::endl;
    //
    std::cout << "Quitting SDL resources........" << std::endl;
    Mix_Quit();
    std::cout << "Mixer successfully closed!" << std::endl;
    TTF_Quit();
    std::cout << "TTF successfully closed!" << std::endl;
    IMG_Quit();
    std::cout << "IMG successfully closed!" << std::endl;

    std::cout << "Quitting SDL........";
    SDL_Quit();
    std::cout << " successfully closed!" << std::endl;
}

bool load_rooms(){
    bool room_flag = true;

    for (int i = 0; i < ROOM_TOTAL; i++){
        std::cout <<  "Room #" << i;
        room_flag = rooms[i].load_room(i);

        if (room_flag)
            std::cout << " successfully loaded!" << std::endl;
        else
            std::cout << " failed to load: " << SDL_GetError() << std::endl;
    }

    return room_flag;
}
