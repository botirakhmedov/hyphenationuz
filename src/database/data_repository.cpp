#include "data_repository.h"
#include "parameters.h"

// #pragma warning (disable:4127)
// #pragma warning (disable:4244)
// #pragma warning (disable:4706)
#define SQLITE_ENABLE_COLUMN_METADATA
#include "sqlite3.h"

namespace database{

error_data repository::insert_word(dto::word_unit in_unit)
{
    sqlite3* db; 
    int result_code = sqlite3_open("example.db", &db); 

    if (result_code) {
        sqlite3_close(db);
        return {error_code::ge_database_open_error, sqlite3_errmsg (db)};
    }
    else {
        char *exec_errmsg;
        
        result_code = sqlite3_exec(db, create_word_table.c_str(), NULL, NULL, &exec_errmsg);
        if(SQLITE_OK != result_code) {
            error_data ret_data {error_code::ge_database_query_error, std::string(exec_errmsg)};
            sqlite3_free(exec_errmsg);
            sqlite3_close(db);
            return ret_data;
        }

        sqlite3_stmt *insert_stmt = NULL;
        int prep_status = sqlite3_prepare_v2(db, insert_word_table.c_str(), -1, &insert_stmt, NULL);

        if (prep_status == SQLITE_OK)
        {
            sqlite3_bind_text(insert_stmt, 1, in_unit.target_word.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(insert_stmt, 2, in_unit.syllable.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(insert_stmt, 3, in_unit.hyphenation.c_str(), -1, SQLITE_STATIC);

            prep_status = sqlite3_step(insert_stmt);
        }

    }
    
    sqlite3_close(db);
    return {error_code::ge_ok, "ok"};
}

} // namespace database
