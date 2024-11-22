#include "word_extractor.h"

const std::string stop_symbols {" {}()/|\\.,[]?\t\n\r"};
std::string word_extractor::get_clean_word(const std::string &inp_word)
{
    auto charpointer = inp_word.c_str();
    for(size_t i = 0; i < inp_word.size(); i++)
    {
        if(stop_symbols.find(inp_word.at(i) != std::string::npos))
        {

        }
    }
    return std::string();
}