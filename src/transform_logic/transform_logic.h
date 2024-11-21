#pragma once
#include <string>
#include <list>
#include "word_info_model.h"

class transform_logic
{
    public:
    transform_logic(){}
    word_info analyze_word(const std::string& inp_word);
    std::string get_clean_word(const std::string& inp_word);
    void replace_all(std::string& source, const std::string &search, const std::string &replace);
    std::list<std::string> word_to_letters(std::string inp_word);
    std::string word_to_syllable(std::string inp_word);
    std::string syllable_to_hyphenation(std::string inp_word);
};
