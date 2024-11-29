#pragma once
#include <string>
#include <list>
#include "commondto.h"

class text_transformer
{
    public:
        text_transformer(){}
        
        dto::word_unit analyze_word(const std::string& inp_word);
        void replace_all(std::string& source, const std::string &search, const std::string &replace);
        std::list<std::string> word_to_letters(std::string inp_word);
};
