#include <filesystem>
#include <fstream>
#include <iostream>

#include <cxxopts.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "config.hpp"
#include "action_point.h"

using json = nlohmann::json;
namespace fs = std::filesystem;

int main(int argc, char **argv)
{
    std::string test_word {"alangali"};
    core::action_point action_point_object;
    action_point_object.file_to_database("C:/Users/botir/lugat.txt", [&](std::string out_data){
        std::cout << out_data << std::endl;
        return error_code::ge_ok;
    });
    
    // const auto welcome_message =
    //     fmt::format("Welcome to {} v{}\n", project_name, project_version);
    // spdlog::info(welcome_message);

    // cxxopts::Options options(project_name.data(), welcome_message);

    // options.add_options("arguments")("h,help", "Print usage")(
    //     "f,filename",
    //     "File name",
    //     cxxopts::value<std::string>())(
    //     "v,verbose",
    //     "Verbose output",
    //     cxxopts::value<bool>()->default_value("false"));

    // auto result = options.parse(argc, argv);

    // if (argc == 1 || result.count("help"))
    // {
    //     std::cout << options.help() << '\n';
    //     return 0;
    // }

    // auto filename = std::string{};
    // auto verbose = false;

    // if (result.count("filename"))
    // {
    //     filename = result["filename"].as<std::string>();
    // }
    // else
    // {
    //     return 1;
    // }

    // verbose = result["verbose"].as<bool>();

    // if (verbose)
    // {
    //     fmt::print("Opening file: {}\n", filename);
    // }

    // auto ifs = std::ifstream{filename};

    // if (!ifs.is_open())
    // {
    //     return 1;
    // }

    // const auto parsed_data = json::parse(ifs);

    // if (verbose)
    // {
    //     const auto name = parsed_data["name"];
    //     fmt::print("Name: {}\n", name);
    // }

    return 0;
}
