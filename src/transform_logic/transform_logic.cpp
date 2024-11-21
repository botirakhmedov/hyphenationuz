#include "transform_logic.h"
#include "interface.h"
#include <vector>
#include <boost/algorithm/string.hpp>

void transform_logic::test()
{
    std::shared_ptr<repository> repo = std::make_shared<repository>();
    repo->test();
}

std::list<std::string> transform_logic::word_to_letters(std::string inp_word)
{
    char tmp = '\2';
    std::string tstr {"\\230"};
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
