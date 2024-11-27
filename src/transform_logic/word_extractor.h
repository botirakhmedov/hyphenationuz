#pragma once

#include <string>
#include <vector>

namespace word_extractor{

    std::string get_clean_word(const std::string& inp_word);
    std::string convert_to_one_letter_ascii(const std::string& inp_word);
    std::vector<std::string> split_to_syllables(const std::string& inp_word);
    std::vector<std::string> hyphenation_from_syllables(const std::vector<std::string>& inp_data);
    std::string vector_to_dashed_string(const std::vector<std::string>& inp_vector);
    void replace_all(std::string &source, const std::string &search, const std::string &replace);
}