#include "core_error.h"
#include <functional>
#include "commondto.h"

namespace core{
    class action_point{
        public:
            action_point(){}
            core_error_code file_to_database(std::string file_name, std::function<void(std::string)> out_info);
            std::vector<dto::word_unit> get_all_words(std::function<void(std::string)> out_info);
            core_error_code update_word(dto::word_unit word_to_update, std::function<void(std::string)> out_info);

            core_error_code generate_latex_hyphenation_file(std::string file_name, std::function<void(std::string)> out_info);
            core_error_code generate_dictionary_file(std::string file_name, std::function<void(std::string)> out_info);

    };
}