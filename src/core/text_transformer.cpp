#include "transform_logic.h"
#include "interface.h"
#include <vector>

dto::word_unit text_transformer::analyze_word(const std::string &inp_word)
{
    return dto::word_unit();
}

void text_transformer::replace_all(std::string &source,
                                  const std::string &search,
                                  const std::string &replace)
{
    size_t pos = 0;
    while ((pos = source.find(search, pos)) != std::string::npos) {
         source.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}

std::list<std::string> text_transformer::word_to_letters(std::string inp_word)
{
    char tmp = 0;
    std::vector<char> data(inp_word.begin(), inp_word.end());
    for(int i = 0; i<data.size(); i++){
        char ichr = data.at(i);
        tmp = ichr;
    }
    return std::list<std::string>();
}
