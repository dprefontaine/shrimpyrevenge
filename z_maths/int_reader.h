#ifndef INT_READER_H_INCLUDED
#define INT_READER_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <string>

class file_reader{
public:
    //CONSTRUCTOR
    //
    file_reader(int data_length = 1);
    //DESTRUCTOR
    //
    ~file_reader();
    //FILE SEARCHING
    //
    bool find_file(std::string file_name);
    //FILE READING
    //
    void read_bin_file(std::string file_name);
    //FILE WRITING
    //
    void write_bin_file(std::string file_name);
    //DATA ACCESSOR AND MUTATOR
    //
    Sint32 get_data(int index = 0);
    void set_data(Sint32 data_point = 0, int index = 0);

private:
    Sint32* data;
    int length;
};

#endif // INT_READER_H_INCLUDED
