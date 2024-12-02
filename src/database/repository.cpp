#include "repository.h"
#include "parameters.h"
#include "dbwrapper.h"

// #pragma warning (disable:4127)
// #pragma warning (disable:4244)
// #pragma warning (disable:4706)
//#define SQLITE_ENABLE_COLUMN_METADATA
//#include "sqlite3.h"

namespace database{

db_error repository::insert_word(dto::word_unit in_unit)
{

    dbw db_wrapper;
    db_error dbr = db_wrapper.open("C:/projects/dictionary/hyphenationuz/example.db");
    if(dbr.code != db_error_code::db_ok){
        return dbr;
    }
    dbr = db_wrapper.execute_sql_noreturn(create_word_table);
    if(dbr.code != db_error_code::db_ok){
        db_wrapper.close();
        return dbr;
    }

    std::vector<std::variant<std::string, int, double>> in_values;
    in_values.push_back(in_unit.target_word);
    in_values.push_back(in_unit.syllable);
    in_values.push_back(in_unit.hyphenation);

    dbr = db_wrapper.insert_word(insert_word_table, in_unit.target_word,in_unit.syllable,in_unit.hyphenation);
    if(dbr.code != db_error_code::db_ok){
        db_wrapper.close();
        return dbr;
    }
    db_wrapper.close();

    // sqlite3* db; 
    // int result_code = sqlite3_open("C:/projects/dictionary/hyphenationuz/example.db", &db); 

    // if (result_code) {
    //     sqlite3_close(db);
    //     return {db_error_code::db_database_open_error, sqlite3_errmsg (db)};
    // }
    // else {
    //     char *exec_errmsg;
        
    //     result_code = sqlite3_exec(db, create_word_table.c_str(), NULL, NULL, &exec_errmsg);
    //     if(SQLITE_OK != result_code) {
    //         db_error ret_data {db_error_code::db_database_query_error, std::string(exec_errmsg)};
    //         sqlite3_free(exec_errmsg);
    //         sqlite3_close(db);
    //         return ret_data;
    //     }

    //     sqlite3_stmt *insert_stmt = NULL;
    //     int prep_status = sqlite3_prepare_v2(db, insert_word_table.c_str(), -1, &insert_stmt, NULL);

    //     if (prep_status == SQLITE_OK)
    //     {
    //         sqlite3_bind_text(insert_stmt, 1, in_unit.target_word.c_str(), -1, SQLITE_STATIC);
    //         sqlite3_bind_text(insert_stmt, 2, in_unit.syllable.c_str(), -1, SQLITE_STATIC);
    //         sqlite3_bind_text(insert_stmt, 3, in_unit.hyphenation.c_str(), -1, SQLITE_STATIC);

    //         prep_status = sqlite3_step(insert_stmt);
    //         if(prep_status != SQLITE_ROW ){

    //         }
    //         sqlite3_finalize(insert_stmt);
    //         //rc = sqlite3_reset( stmt );
    //     }

    // }
    
    // sqlite3_close(db);
    return {db_error_code::db_ok, "ok"};
}

db_error repository::update_word(std::string word_to_update, dto::word_unit in_unit)
{
    return {db_error_code::db_ok, ""};
}

dbresult<dto::word_unit> repository::find_word(std::string word_to_find)
{
    return db_error_code::db_ok;
}

} // namespace database
