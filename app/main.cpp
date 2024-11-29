#include <filesystem>
#include <fstream>
#include <iostream>

#include <cxxopts.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "config.hpp"
//#include "interface.h"
#include "text_transformer.h"
//#include "word_extractor.h"

using json = nlohmann::json;
namespace fs = std::filesystem;

int main(int argc, char **argv)
{
    std::string test_word {"alang-alangai"};
    //std::vector<std::string> s_list = word_extractor::split_to_syllables(test_word);
    
    //std::cout << word_extractor::vector_to_dashed_string(s_list) << std::endl; 

    //std::vector<std::string> h_list = word_extractor::hyphenation_from_syllables(s_list);
    //std::cout << word_extractor::vector_to_dashed_string(h_list) << std::endl; 
    const auto welcome_message =
        fmt::format("Welcome to {} v{}\n", project_name, project_version);
    spdlog::info(welcome_message);

    cxxopts::Options options(project_name.data(), welcome_message);

    options.add_options("arguments")("h,help", "Print usage")(
        "f,filename",
        "File name",
        cxxopts::value<std::string>())(
        "v,verbose",
        "Verbose output",
        cxxopts::value<bool>()->default_value("false"));

    auto result = options.parse(argc, argv);

    if (argc == 1 || result.count("help"))
    {
        std::cout << options.help() << '\n';
        return 0;
    }

    auto filename = std::string{};
    auto verbose = false;

    if (result.count("filename"))
    {
        filename = result["filename"].as<std::string>();
    }
    else
    {
        return 1;
    }

    verbose = result["verbose"].as<bool>();

    if (verbose)
    {
        fmt::print("Opening file: {}\n", filename);
    }

    auto ifs = std::ifstream{filename};

    if (!ifs.is_open())
    {
        return 1;
    }

    const auto parsed_data = json::parse(ifs);

    if (verbose)
    {
        const auto name = parsed_data["name"];
        fmt::print("Name: {}\n", name);
    }

    return 0;
}
