#include "error_code.h"
#include <functional>

namespace core{
    class action_point{
        public:
            action_point(){}
            error_code file_to_database(std::string file_name, std::function<error_code(std::string)> out_info);
    };
}