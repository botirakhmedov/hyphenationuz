#pragma once
#include <string>
#include <list>

class transform_logic
{
    public:
    transform_logic(){}
    void test();
    std::list<std::string> word_to_letters(std::string inp_word);
    std::string word_to_syllable(std::string inp_word);
    std::string syllable_to_hyphenation(std::string inp_word);
};