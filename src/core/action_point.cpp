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
}
