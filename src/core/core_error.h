#pragma once
#include <string>

namespace core{
enum core_error_code{
    ge_ok,
    ge_unknown,
    ge_no_data,
    ge_unable_open_file,
    ge_database_open_error,
    ge_database_query_error
};

struct core_error{
    core_error_code code;
    std::string information;
};
}