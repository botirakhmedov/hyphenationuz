#include "transform_logic.h"
#include "interface.h"
#include <vector>

word_info transform_logic::analyze_word(const std::string &inp_word)
{
    return word_info();
}

std::string transform_logic::get_clean_word(const std::string &inp_word)
{
    auto charpointer = inp_word.c_str();
    for(size_t i = 0; i < inp_word.size(); i++)
    {
        
    }
    return std::string();
}

void transform_logic::replace_all(std::string &source,
                                  const std::string &search,
                                  const std::string &replace)
{
    size_t pos = 0;
    while ((pos = source.find(search, pos)) != std::string::npos) {
         source.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}

std::list<std::string> transform_logic::word_to_letters(std::string inp_word)
{
    char tmp = 0;
    std::vector<char> data(inp_word.begin(), inp_word.end());
    for(int i = 0; i<data.size(); i++){
        char ichr = data.at(i);
        tmp = ichr;
    }
    return std::list<std::string>();
}

std::string transform_logic::word_to_syllable(std::string inp_word)
{
    return std::string();
}

std::string transform_logic::syllable_to_hyphenation(std::string inp_word)
{
    return std::string();
}
