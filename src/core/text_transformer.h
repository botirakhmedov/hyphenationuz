#pragma once
#include <string>
#include <list>
#include <vector>
#include <map>
#include "commondto.h"
#include "result.h"

class text_transformer
{
    public:
        text_transformer(){}
        
        result<dto::word_unit> analyze_word(const std::string& inp_word);

    private:
        void replace_all(std::string& source, const std::string &search, const std::string &replace);
        std::string get_clean_word(const std::string& inp_word);
        std::string convert_to_one_letter_ascii(const std::string& inp_word);
        std::vector<std::string> split_to_syllables(const std::string& inp_word);
        std::vector<std::string> hyphenation_from_syllables(const std::vector<std::string>& inp_data);
        std::string vector_to_dashed_string(const std::vector<std::string>& inp_vector);
        size_t find_start_index(const std::string & inp_word);
        size_t find_length(const std::string & inp_word, size_t start_index =0);

        static const std::string stop_symbols;
        static const std::map<std::string, std::string> change_map;
        static const std::map<std::string, std::string> digraph_map;
        static const std::string vowels;
};
