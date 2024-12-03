#pragma once
#include <vector>
#include "db_error.h"
namespace database{
template <class T>class dbresult{
    public:
        dbresult() = delete;
        dbresult(std::vector<T>& inp_data):result_error(db_error_code::db_ok){
            is_has_error = false;
            result_data = std::move(inp_data);
        }
        dbresult(T inp_data):result_error(db_error_code::db_ok){
            is_has_error = false;
            result_data.push_back(inp_data);
        }
        dbresult(db_error_code er_code):result_error(er_code){
            is_has_error = true;
        }
        dbresult(db_error er):result_error(er){
            is_has_error = true;
        }
        bool has_error(){
            return is_has_error;
        }
        std::vector<T> data(){
            return result_data;
        }
        db_error error()
        {
            return result_error;
        }
    private:
        std::vector<T> result_data;
        bool is_has_error;
        db_error result_error;
};
}