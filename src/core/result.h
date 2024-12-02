#pragma once
#include "core_error.h"
namespace core{
template <class T>class result{
    public:
        result() = delete;

        result(T inp_data){
            result_error.code = core_error_code::ge_ok;
            is_has_error = false;
            result_data = inp_data;
        }
        result(core_error_code er_code){
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
        core_error error()
        {
            return result_error;
        }
    private:
        T result_data;
        bool is_has_error;
        core_error result_error;
};
}