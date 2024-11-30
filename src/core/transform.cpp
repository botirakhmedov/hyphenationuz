#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
#include "transform.h"

namespace core{

/// @brief 
const std::string transform::stop_symbols = {" {}()/|\\.,[]?:;\t\n\r"};

const std::map<std::string, std::string> transform::change_map = {
    {"‘","`"},
    {"’","'"}
};

const std::map<std::string, std::string> transform::digraph_map = {
    {"o`","0"},
    {"g`","9"},
    {"ch","c"},
    {"sh","w"}
};

const std::string transform::vowels = {"aeuoi0"};

size_t transform::find_start_index(const std::string &inp_word)
{
    char cur_char = 0;
    for(size_t i = 0; i < inp_word.size(); i++)
    {
        cur_char = inp_word.at(i);
        if((cur_char>='A' && cur_char<='Z') || (cur_char>='a' && cur_char<='z'))
        {
            return i;
        }
    }
    return inp_word.size();
}

size_t transform::find_length(const std::string &inp_word, size_t start_index)
{
    for(size_t i = start_index; i < inp_word.size(); i++)
    {
        if(stop_symbols.find(inp_word.at(i)) != std::string::npos)
        {
            return i - start_index;
        }
    }
    return inp_word.size();
}

void transform::replace_all(std::string &source, const std::string &search, const std::string &replace)
{
    size_t pos = 0;
    while ((pos = source.find(search, pos)) != std::string::npos) {
         source.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}

std::string transform::get_clean_word(const std::string &inp_word)
{
    std::string internal_copy = inp_word;

    size_t start_index = find_start_index(inp_word);
    size_t word_length = find_length(inp_word, start_index);

    return inp_word.substr(start_index, word_length);
}

std::string transform::convert_to_one_letter_ascii(const std::string &inp_word)
{
    std::string internal_copy = inp_word;
    std::transform(internal_copy.begin(), internal_copy.end(), internal_copy.begin(), ::tolower);
    for(const auto& [key, value]:change_map)
    {
        replace_all(internal_copy, key, value);
    }
    
    for(const auto& [key, value]:digraph_map)
    {
        replace_all(internal_copy, key, value);    
    }
    return internal_copy;
}

std::vector<std::string> transform::split_to_syllables(const std::string &inp_word)
{
    std::vector<std::string> ret_val;
    if(inp_word.size() <= 3)
    {
        ret_val.push_back(inp_word);
    }
    else
    {
        std::string tmp_syllable;
        std::vector<size_t> vowel_indexes;
        for(size_t index = 0; index < inp_word.size(); index++)
        {
            if(vowels.find(inp_word.at(index)) != std::string::npos)
            {
                vowel_indexes.push_back(index);
            }
        }

        if(vowel_indexes.size() > 1)
        {
            size_t start_syllable_index = 0;
            for(size_t vowel_index = 0; vowel_index < vowel_indexes.size(); vowel_index++)
            {
                if(vowel_index < (vowel_indexes.size() - 1))
                {
                    size_t first_index = vowel_indexes.at(vowel_index) + 1;
                    //size_t second_index = vowel_indexes.at(vowel_index + 1);
                    size_t space = vowel_indexes.at(vowel_index + 1) - first_index;
                    std::string sub_str = inp_word.substr(first_index, space);
                    size_t t_index = 0;
                    size_t size_of_syllable = 0;
                    if((t_index = sub_str.find('-')) != std::string::npos)
                    {
                        size_of_syllable = first_index + t_index - start_syllable_index;
                        tmp_syllable = inp_word.substr(start_syllable_index, size_of_syllable);
                        ret_val.push_back(tmp_syllable);
                        start_syllable_index += (size_of_syllable + 1);
                    }
                    else if((t_index = sub_str.find('\'')) != std::string::npos)
                    {
                        size_of_syllable = first_index + t_index - start_syllable_index + 1;
                        tmp_syllable = inp_word.substr(start_syllable_index, size_of_syllable);
                        ret_val.push_back(tmp_syllable);
                        start_syllable_index += size_of_syllable;
                    }
                    else
                    {
                        bool has_pair_letters = false;
                        for(size_t sub_index = 1; sub_index < space; sub_index++)
                        {
                            size_t actual_index = sub_index + first_index;
                            if(inp_word.at(actual_index) == inp_word.at(actual_index - 1))
                            {
                                size_of_syllable = actual_index - start_syllable_index ;
                                tmp_syllable = inp_word.substr(start_syllable_index, size_of_syllable);
                                ret_val.push_back(tmp_syllable);
                                start_syllable_index += size_of_syllable;
                                has_pair_letters = true;
                            }
                        }

                        if(!has_pair_letters)
                        {
                            size_of_syllable = space/2 + first_index - start_syllable_index;
                            tmp_syllable = inp_word.substr(start_syllable_index, size_of_syllable);
                            ret_val.push_back(tmp_syllable);
                            start_syllable_index += size_of_syllable;
                        }
                    }
                }
                else
                {
                    tmp_syllable = inp_word.substr(start_syllable_index);
                    ret_val.push_back(tmp_syllable);
                }
            }
        }
        else
        {
            ret_val.push_back(inp_word);
        }
    }
    return ret_val;
}

std::vector<std::string> transform::hyphenation_from_syllables(const std::vector<std::string> &inp_data)
{
    if(inp_data.size() > 1)
    {
        std::vector<std::string> ret_val;
        size_t start_index = 0;
        if(inp_data.front().size() == 1)
        {
            std::ostringstream first_item_string;
            first_item_string << inp_data.at(0) << inp_data.at(1);
            ret_val.push_back(first_item_string.str());
            start_index = 2;
        }
        for(size_t i = start_index; i < inp_data.size()-1; i++)
        {
            ret_val.push_back(inp_data.at(i));
        }
        if(inp_data.back().size() == 1)
        {
            std::ostringstream last_item_string;
            last_item_string << ret_val.back() << inp_data.back();
            ret_val.back() = last_item_string.str();
        }
        else
        {
            ret_val.push_back(inp_data.back());
        }
        return ret_val;
    }
    return inp_data;
}

std::string transform::vector_to_dashed_string(const std::vector<std::string> &inp_vector)
{
    if(inp_vector.empty())
    {
        return std::string();
    }
    std::ostringstream out_string;
    out_string << inp_vector.at(0);
    for(size_t i = 1; i < inp_vector.size(); i++)
    {
        out_string << "-" << inp_vector.at(i);
    }
    return out_string.str();
}

result<dto::word_unit> transform::analyze_word(const std::string &inp_word)
{
    std::string clean_word = get_clean_word(inp_word);
    if(clean_word.empty())
    {
        return error_code::ge_no_data;
    }
    std::string ascii_str = convert_to_one_letter_ascii(clean_word);
    auto syllable_vector = split_to_syllables(ascii_str);
    auto hyphenation_vector = hyphenation_from_syllables(syllable_vector);
    dto::word_unit return_value;
    return_value.target_word = ascii_str;
    return_value.syllable = vector_to_dashed_string(syllable_vector);
    return_value.hyphenation = vector_to_dashed_string(hyphenation_vector);
    return return_value;
}

std::vector<std::string> transform::string_to_words(const std::string &in_string)
{
    std::vector<std::string> ret_value;
    std::stringstream ss(in_string);
    std::string buf_str;
  	// Delimiter
    char del = ' ';
   	// Splitting the str string by delimiter
    while (std::getline(ss, buf_str, del))
    {
        if(!buf_str.empty())
        {
            ret_value.push_back(buf_str);
        }
    }
    return ret_value;
}
} // namespace core