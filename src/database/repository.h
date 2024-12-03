#include "commondto.h"
#include "dbresult.h"

namespace database{

    class repository
    {
        public:
            repository(){}
            db_error insert_word(dto::word_unit in_unit);
            db_error update_word(dto::word_unit in_unit);
            dbresult<dto::word_unit> find_word(std::string word_to_find);
            dbresult<dto::word_unit> get_all_words();
            
        private:

    };
}

