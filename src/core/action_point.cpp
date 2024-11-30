#include "action_point.h"
#include <iostream>
#include <fstream>
#include <string>

error_code core::action_point::file_to_database(std::string file_name, std::function<error_code(std::string)> out_info)
{
    auto input_file = std::ifstream{file_name};

    if (!input_file.is_open())
    {
        return error_code::ge_unable_open_file;
    }
    std::string file_line; 
    while (std::getline(input_file, file_line))
    {
        // Process str
    }
    return error_code::ge_ok;
}