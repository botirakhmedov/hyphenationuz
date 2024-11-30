#pragma once
#include <string>

enum error_code{
    ge_ok,
    ge_unknown,
    ge_no_data,
    ge_unable_open_file
};

struct error_data{
    error_code code;
    std::string information;
};
