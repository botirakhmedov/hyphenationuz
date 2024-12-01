#include "commondto.h"
#include "result.h"

namespace database{

    class repository
    {
        public:
            repository(){}
            error_data insert_word(dto::word_unit in_unit);
            error_data update_word(std::string word_to_update, dto::word_unit in_unit);
            result<dto::word_unit> find_word(std::string word_to_find);
            
        private:

    };
}

