#pragma once
#include <string>

namespace database{

enum db_error_code{
    db_ok,
    db_unknown,
    db_database_open_error,
    db_database_query_error
};

struct db_error{
    db_error(db_error_code in_code){
        code = in_code;
    }
    db_error(db_error_code in_code, std::string info){
        code = in_code;
        information = info;
    }
    db_error_code code;
    std::string information;
};

}
