#pragma once
#include <string>

enum error_code{
    ge_ok,
    ge_no_data,
    ge_unknown
};

struct error_data{
    error_code code;
    std::string information;
};
