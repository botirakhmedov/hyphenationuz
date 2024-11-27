#include "word_extractor.h"
#include <map>
#include <algorithm>

const std::string stop_symbols {" {}()/|\\.,[]?:;\t\n\r"};

const std::map<std::string, std::string> change_map {
    {"‘","`"},
    {"’","'"}
};

const std::map<std::string, std::string> digraph_map {
    {"o`","0"},
    {"g`","9"},
    {"ch","c"},
    {"sh","w"}
};

const std::string vowels {"aeuoi0"};

size_t find_start_index(const std::string & inp_word)
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
    return 0;
}

size_t find_length(const std::string & inp_word, size_t start_index =0)
{
    for(size_t i = start_index; i < inp_word.size(); i++)
    {
        if(stop_symbols.find(inp_word.at(i)) != std::string::npos)
        {
            return i - start_index;
        }
    }
    return 0;
}

std::string word_extractor::get_clean_word(const std::string &inp_word)
{
    std::string internal_copy = inp_word;

    //std::transform(internal_copy.begin(), internal_copy.end(), internal_copy.begin(), ::tolower);
    size_t start_index = find_start_index(inp_word);
    size_t word_length = find_length(inp_word, start_index);

    return inp_word.substr(start_index, word_length);
}

std::string word_extractor::convert_to_one_letter_ascii(const std::string &inp_word)
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

std::vector<std::string> word_extractor::split_to_syllables(const std::string &inp_word)
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
                    size_t second_index = vowel_indexes.at(vowel_index+1);
                    size_t space = second_index - first_index;
                    std::string sub_str = inp_word.substr(first_index, space);
                    size_t t_index = sub_str.find('-');
                    if(t_index != std::string::npos)
                    {
                        tmp_syllable = inp_word.substr(start_syllable_index, t_index - start_syllable_index);
                        ret_val.push_back(tmp_syllable);
                        start_syllable_index = t_index + 2;
                    }
                    else if((t_index = sub_str.find('\'')) != std::string::npos)
                    {
                        tmp_syllable = inp_word.substr(start_syllable_index, t_index - start_syllable_index + 1);
                        ret_val.push_back(tmp_syllable);
                        start_syllable_index = t_index + 2;
                    }
                    else if(space == 1)
                    {
                        tmp_syllable = inp_word.substr(start_syllable_index, first_index - start_syllable_index);
                        ret_val.push_back(tmp_syllable);
                        start_syllable_index += first_index - start_syllable_index;
                    }
                    else
                    {
                        bool has_pair_letters = false;
                        for(size_t sub_index = 1; sub_index < space; sub_index++)
                        {
                            size_t actual_index = sub_index + first_index;
                            if(inp_word.at(actual_index) == inp_word.at(actual_index - 1))
                            {
                                tmp_syllable = inp_word.substr(start_syllable_index, actual_index - start_syllable_index);
                                ret_val.push_back(tmp_syllable);
                                start_syllable_index = actual_index;
                                has_pair_letters = true;
                            }
                        }

                        if(!has_pair_letters)
                        {
                            size_t size_of_syllable = space/2 + first_index - start_syllable_index;
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

std::vector<std::string> word_extractor::hyphenation_from_syllables(
    const std::vector<std::string> &inp_data)
{

    return std::vector<std::string>();
}

void word_extractor::replace_all(std::string &source,
                                  const std::string &search,
                                  const std::string &replace)
{
    size_t pos = 0;
    while ((pos = source.find(search, pos)) != std::string::npos) {
         source.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}