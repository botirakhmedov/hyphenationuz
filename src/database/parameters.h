#include <string>

namespace database{

const std::string create_word_table {"create table if not exists words "
                                        "(id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                        "target_word TEXT UNIQUE,"
                                        "syllable TEXT UNIQUE,"
                                        "hyphenation TEXT UNIQUE);"
                                        };
const std::string select_word_table {"select * from words where target_word=?;"};
const std::string selectall_word_table {"select * from words;"};
const std::string insert_word_table {"insert into words (target_word,syllable,hyphenation) values (?,?,?)"};
const std::string update_word_table {"update words set target_word=?,syllable=?,hyphenation=? where target_word=?"};

}