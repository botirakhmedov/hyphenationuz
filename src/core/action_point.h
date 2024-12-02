#include "core_error.h"
#include <functional>

namespace core{
    class action_point{
        public:
            action_point(){}
            core_error_code file_to_database(std::string file_name, std::function<void(std::string)> out_info);
    };
}