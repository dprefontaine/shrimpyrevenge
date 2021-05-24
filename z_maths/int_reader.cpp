#include <z_maths/int_reader.h>

file_reader::file_reader(int data_length){
    file_reader::data = new Sint32[data_length];
    file_reader::length = data_length;
}

file_reader::~file_reader(){
    delete [] file_reader::data;
}

bool file_reader::find_file(std::string file_name){
    //FIND THE FILE
    //
    SDL_RWops* file = SDL_RWFromFile(file_name.c_str(),"w+b");

    return (file != NULL);
}

void file_reader::read_bin_file(std::string file_name){
    //FIND THE FILE
    //
    SDL_RWops* file = SDL_RWFromFile(file_name.c_str(),"w+b");

    if (file == NULL){
        std::cout << "Failed to read file of " << file_name.c_str() << " : " << SDL_GetError() << std::endl;
    } else {
        //READING FILE
        //
        for (int i = 0; i < file_reader::length; i++){
            SDL_RWread(file, &file_reader::data[i],sizeof(Sint32),1);
        }
        SDL_RWclose(file);
    }
}

void file_reader::write_bin_file(std::string file_name){
    //CHECK IF FILE EXISTS
    //
    if (!(file_reader::find_file(file_name))){
        //CREATE A NEW FILE
        //
        SDL_RWops* new_file = SDL_RWFromFile(file_name.c_str(),"w+b");
        //

        //ADD CONTENTS TO THE FILE
        //
        for (int i = 0; i < file_reader::length; i++){
            SDL_RWwrite(new_file,&file_reader::data[i],sizeof(Sint32),1);
        }
        SDL_RWclose(new_file);
    } else {
        std::cout << "The file directory already exists!" << std::endl;
    }
}

Sint32 file_reader::get_data(int index){
    if (file_reader::length > index)
        return file_reader::data[index];
    else
        return -1;
}

