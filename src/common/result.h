#pragma once
#include "error_code.h"

template <class T>class result{
    public:
        result() = delete;

        result(T inp_data){
            result_error.code = error_code::ge_ok;
            is_has_error = false;
            result_data = inp_data;
        }
        result(error_code er_code){
            result_data = T();
            result_error.code = er_code;
            is_has_error = true;
        }
        bool has_error(){
            return is_has_error;
        }
        T data(){
            return result_data;
        }
        error_data error()
        {
            return result_error;
        }
    private:
        T result_data;
        bool is_has_error;
        error_data result_error;
};
