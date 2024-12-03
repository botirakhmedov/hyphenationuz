#include "dbwrapper.h"
#include "parameters.h"

namespace database{
db_error dbw::open(std::string file_path)
{
    database_file = file_path;
    int result_code = sqlite3_open(database_file.c_str(), &db); 

    if (result_code) {
        sqlite3_close(db);
        return {db_error_code::db_database_open_error, sqlite3_errmsg (db)};
    }
    return db_error_code::db_ok;
}

db_error dbw::close()
{
    if(db != NULL){
        if(sqlite3_close(db) != SQLITE_OK){
            return {db_error_code::db_unknown, sqlite3_errmsg (db)};
        }
    }
    return db_error_code::db_ok;
}

db_error dbw::execute_sql_noreturn(std::string sql_statement)
{
    char *exec_errmsg;
    if(SQLITE_OK != sqlite3_exec(db, sql_statement.c_str(), NULL, NULL, &exec_errmsg)) {
        db_error ret_data {db_error_code::db_database_query_error, std::string(exec_errmsg)};
        sqlite3_free(exec_errmsg);
        sqlite3_close(db);
        return ret_data;
    }
    return db_error_code::db_ok;
}

db_error dbw::insert_word(std::string target, std::string syllable, std::string hyphenation)
{
    sqlite3_stmt *insert_stmt = NULL;
    int prep_status = sqlite3_prepare_v2(db, insert_word_table.c_str(), -1, &insert_stmt, NULL);

    if (prep_status == SQLITE_OK)
    {
        sqlite3_bind_text(insert_stmt, 1, target.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(insert_stmt, 2, syllable.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(insert_stmt, 3, hyphenation.c_str(), -1, SQLITE_STATIC);
        prep_status = sqlite3_step(insert_stmt);
        if(prep_status != SQLITE_DONE){
            sqlite3_finalize(insert_stmt);    
            return db_error_code::db_database_query_error;
        }
        sqlite3_finalize(insert_stmt);
    }
    return db_error_code::db_ok;
}

db_error dbw::update_word(std::string target, std::string syllable, std::string hyphenation)
{
    sqlite3_stmt *update_stmt = NULL;
    int prep_status = sqlite3_prepare_v2(db, update_word_table.c_str(), -1, &update_stmt, NULL);

    if (prep_status == SQLITE_OK)
    {
        sqlite3_bind_text(update_stmt, 1, syllable.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(update_stmt, 2, hyphenation.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(update_stmt, 3, target.c_str(), -1, SQLITE_STATIC);
        prep_status = sqlite3_step(update_stmt);
        if(prep_status != SQLITE_DONE){
            sqlite3_finalize(update_stmt);    
            return db_error_code::db_database_query_error;
        }
        sqlite3_finalize(update_stmt);
    }
    return db_error_code::db_ok;
}

dbresult<dto::word_unit> dbw::select_word_all()
{
    sqlite3_stmt *select_stmt = NULL;
    int prep_status = sqlite3_prepare_v2(db, selectall_word_table.c_str(), -1, &select_stmt, NULL);

    if (prep_status == SQLITE_OK)
    {
        dbresult<dto::word_unit> ret_val(db_error_code::db_ok);
        std::vector<dto::word_unit> rows;
        while (sqlite3_step(select_stmt) == SQLITE_ROW) {
            dto::word_unit r_word;
            r_word.target_word = reinterpret_cast<const char*>(sqlite3_column_text(select_stmt, 0));
            r_word.syllable = reinterpret_cast<const char*>(sqlite3_column_text(select_stmt, 1));
            r_word.hyphenation = reinterpret_cast<const char*>(sqlite3_column_text(select_stmt, 2));
            rows.push_back(r_word);
        }
        sqlite3_finalize(select_stmt);
        return rows;
    }
    return db_error_code::db_database_query_error;
}

dbresult<dto::word_unit> dbw::select_word(std::string key_word)
{
    sqlite3_stmt *select_stmt = NULL;
    int prep_status = sqlite3_prepare_v2(db, select_word_table.c_str(), -1, &select_stmt, NULL);

    if (prep_status == SQLITE_OK)
    {
        sqlite3_bind_text(select_stmt, 1, key_word.c_str(), -1, SQLITE_STATIC);
        
        dbresult<dto::word_unit> ret_val(db_error_code::db_ok);
        std::vector<dto::word_unit> rows;
        while (sqlite3_step(select_stmt) == SQLITE_ROW) {
            dto::word_unit r_word;
            r_word.target_word = reinterpret_cast<const char*>(sqlite3_column_text(select_stmt, 0));
            r_word.syllable = reinterpret_cast<const char*>(sqlite3_column_text(select_stmt, 1));
            r_word.hyphenation = reinterpret_cast<const char*>(sqlite3_column_text(select_stmt, 2));
            rows.push_back(r_word);
        }
        sqlite3_finalize(select_stmt);
        return rows;
    }
    return db_error_code::db_database_query_error;
}

} // namespace database