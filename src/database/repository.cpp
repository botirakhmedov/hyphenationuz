#include "repository.h"
#include "parameters.h"
#include "dbwrapper.h"
#include <iostream>

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

    dbr = db_wrapper.insert_word(in_unit.target_word,in_unit.syllable,in_unit.hyphenation);
    if(dbr.code != db_error_code::db_ok){
        db_wrapper.close();
        return dbr;
    }
    db_wrapper.close();
    
    return {db_error_code::db_ok, "ok"};
}

db_error repository::update_word(dto::word_unit in_unit)
{
    dbw db_wrapper;
    db_error dbr = db_wrapper.open("C:/projects/dictionary/hyphenationuz/example.db");
    if(dbr.code != db_error_code::db_ok){
        return dbr;
    }

    dbr = db_wrapper.update_word(in_unit.target_word,in_unit.syllable,in_unit.hyphenation);
    if(dbr.code != db_error_code::db_ok){
        db_wrapper.close();
        return dbr;
    }
    db_wrapper.close();
    
    return {db_error_code::db_ok, "ok"};
}

dbresult<dto::word_unit> repository::find_word(std::string word_to_find)
{
    dbw db_wrapper;
    db_error dbr = db_wrapper.open("C:/projects/dictionary/hyphenationuz/example.db");
    if(dbr.code != db_error_code::db_ok){
        return dbr;
    }
    auto dbresult = db_wrapper.select_word(word_to_find);
    if(dbr.code != db_error_code::db_ok){
        db_wrapper.close();
        return dbresult;
    }
    db_wrapper.close();
    return dbresult;
}

dbresult<dto::word_unit> repository::get_all_words()
{
    dbw db_wrapper;
    db_error dbr = db_wrapper.open("C:/projects/dictionary/hyphenationuz/example.db");
    if(dbr.code != db_error_code::db_ok){
        return dbr;
    }
    auto dbresult = db_wrapper.select_word_all();
    if(dbr.code != db_error_code::db_ok){
        db_wrapper.close();
        return dbresult;
    }
    db_wrapper.close();
    return dbresult;
}

} // namespace database
