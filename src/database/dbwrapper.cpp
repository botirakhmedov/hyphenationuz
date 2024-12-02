#include "dbwrapper.h"

//#define SQLITE_ENABLE_COLUMN_METADATA


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

db_error dbw::insert_word(std::string sql_statement, std::string target, std::string sylleble, std::string hyphenation)
{
    sqlite3_stmt *insert_stmt = NULL;
    int prep_status = sqlite3_prepare_v2(db, sql_statement.c_str(), -1, &insert_stmt, NULL);

    if (prep_status == SQLITE_OK)
    {
        sqlite3_bind_text(insert_stmt, 1, target.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(insert_stmt, 2, sylleble.c_str(), -1, SQLITE_STATIC);
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

dbresult<dto::word_unit> dbw::execute_sql(std::string sql_statement)
{
    return db_error_code::db_ok;
}

dbresult<dto::word_unit> dbw::execute(std::string sql_statement, std::vector<std::variant<std::string, int, double>> values)
{
    return db_error_code::db_ok;
}

} // namespace database