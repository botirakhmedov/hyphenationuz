#include "action_point.h"
#include <iostream>
#include <fstream>
#include <string>
#include <format>
#include "transform.h"
#include "repository.h"

namespace core{
core_error_code core::action_point::file_to_database(std::string file_name, std::function<void(std::string)> out_info)
{
    database::repository repo;
    auto input_file = std::ifstream{file_name};
    if(out_info != nullptr){
        out_info("Start file processing!");
    }
    if (!input_file.is_open())
    {
        if(out_info != nullptr){
            out_info(std::format("Error on opening file:{}",file_name));
        }
        return core_error_code::ge_unable_open_file;
    }
    core::transform text_transform;
    std::string file_line; 
    if(out_info != nullptr){
        out_info(std::format("File opened. Start processing...:"));
    }
    
    while (std::getline(input_file, file_line))
    {
        std::vector words(text_transform.string_to_words(file_line));
        for(const auto& w_item : words){
            auto w_result = text_transform.analyze_word(w_item);
            if(w_result.has_error()){
                if(out_info != nullptr){
                    out_info(std::format("problem with:{}", w_item));
                }
            }
            else
            {
                if(w_result.data().target_word.size() > 1){
                    auto res_query = repo.find_word(w_result.data().target_word);
                    if(!res_query.has_error() && res_query.data().size() > 0){
                        if(out_info != nullptr){
                            out_info(std::format("word exists:{} - {}, {}, {}", w_item, 
                                                                w_result.data().target_word,
                                                                w_result.data().syllable,
                                                                w_result.data().hyphenation));
                        }
                        continue;
                    }
                    repo.insert_word(w_result.data());
                    if(out_info != nullptr){
                        out_info(std::format("accept word:{} - {}, {}, {}", w_item, 
                                                                w_result.data().target_word,
                                                                w_result.data().syllable,
                                                                w_result.data().hyphenation));
                    }
                }
            }
        }
    }

    if(out_info != nullptr){
        out_info(std::format("Done!"));
    }
    
    return core_error_code::ge_ok;
}

std::vector<dto::word_unit> action_point::get_all_words(std::function<void(std::string)> out_info)
{
    database::repository repo;
    auto result = repo.get_all_words();
    if(result.has_error()){
        if(out_info != nullptr){
            out_info(std::format("accept word:{}-{}", int(result.error().code), result.error().information));
            return std::vector<dto::word_unit>();
        }
    }
    return result.data();
}

core_error_code action_point::update_word(dto::word_unit word_to_update, std::function<void(std::string)> out_info)
{
    database::repository repo;
    auto result = repo.update_word(word_to_update);
    if(result.code != core_error_code::ge_ok){
        if(out_info != nullptr){
            out_info(std::format("error on update:{}", int(result.code)));
            return core_error_code::ge_database_query_error;
        }
    }
}

core_error_code action_point::generate_latex_hyphenation_file(std::string file_name, std::function<void(std::string)> out_info)
{
    auto out_file = std::ofstream{file_name};
    if(out_info != nullptr){
        out_info("Start file processing!");
    }
    if (!out_file.is_open())
    {
        if(out_info != nullptr){
            out_info(std::format("Error on opening file:{}",file_name));
        }
        return core_error_code::ge_unable_open_file;
    }
    database::repository repo;
    auto words_result = repo.get_all_words();
    if(words_result.has_error()){
        if(out_info != nullptr){
            out_info(std::format("Error on reading database:{} {}", int(words_result.error().code), words_result.error().information));
            return core_error_code::ge_database_query_error;
        }
    }

    out_file << "hyphenation{" << std::endl;
    core::transform text_transform;
    for(const auto& w_item:words_result.data()){
        auto result_string = text_transform.convert_one_letter_ascii_to_regular(w_item.hyphenation, symbol_type::base_simple_digraph);
        out_file << result_string << std::endl;
    }
    out_file << "}" << std::endl;
    out_file.close();
    if(out_info != nullptr){
        out_info("File created!");
    }
    return core_error_code::ge_ok;
}

core_error_code action_point::generate_dictionary_file(std::string file_name, std::function<void(std::string)> out_info)
{
    auto out_file = std::ofstream{file_name};
    if(out_info != nullptr){
        out_info("Start file processing!");
    }
    if (!out_file.is_open())
    {
        if(out_info != nullptr){
            out_info(std::format("Error on opening file:{}",file_name));
        }
        return core_error_code::ge_unable_open_file;
    }
    database::repository repo;
    auto words_result = repo.get_all_words();
    if(words_result.has_error()){
        if(out_info != nullptr){
            out_info(std::format("Error on reading database:{} {}", int(words_result.error().code), words_result.error().information));
            return core_error_code::ge_database_query_error;
        }
    }

    core::transform text_transform;
    for(const auto& w_item:words_result.data()){
        auto result_string = text_transform.convert_one_letter_ascii_to_regular(w_item.target_word, symbol_type::base_simple_digraph);
        out_file << result_string << std::endl;
    }
    out_file.close();
    if(out_info != nullptr){
        out_info("File created!");
    }
    return core_error_code::ge_ok;
}
} // namespace core
