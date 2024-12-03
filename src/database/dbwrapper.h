#include <string>
#include <vector>
#include <variant>
#include "db_error.h"
#include "dbresult.h"
#include "commondto.h"
#include "sqlite3.h"

namespace database{
class dbw{
    public:
        db_error open(std::string file_path);
        db_error close();
        db_error execute_sql_noreturn(std::string sql_statement);
        db_error insert_word(std::string target, std::string sylleble, std::string hyphenation);
        db_error update_word(std::string target, std::string sylleble, std::string hyphenation);
        dbresult<dto::word_unit> select_word_all();
        dbresult<dto::word_unit> select_word(std::string kwy_word);
    private:
        sqlite3* db;
        std::string database_file;
        
};
}