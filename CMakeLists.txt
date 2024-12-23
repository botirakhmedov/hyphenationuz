cmake_minimum_required(VERSION 3.22)

project(
    "hyphenation_splitter"
    VERSION 1.0.0
    LANGUAGES C CXX)

# Global CMake variables are set here
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Options
option(USE_CPM "Whether to use CPM." ON)

option(ENABLE_WARNINGS "Enable to add warnings to a target." ON)
option(ENABLE_WARNINGS_AS_ERRORS "Enable to treat warnings as errors." OFF)

option(ENABLE_TESTING "Enable a Unit Testing build." ON)
option(ENABLE_COVERAGE "Enable a Code Coverage build." OFF)

option(ENABLE_CLANG_TIDY "Enable to add clang tidy." OFF)

option(ENABLE_SANITIZE_ADDR "Enable address sanitize." OFF)
option(ENABLE_SANITIZE_UNDEF "Enable undefined sanitize." OFF)
option(ENABLE_SANITIZE_LEAK "Enable leak sanitize (Gcc/Clang only)." OFF)
option(ENABLE_SANITIZE_THREAD "Enable thread sanitize (Gcc/Clang only)." OFF)

option(ENABLE_CLANG_FORMAT "Enable to add clang-format." OFF)
option(ENABLE_CMAKE_FORMAT "Enable to add cmake-format." OFF)

option(ENABLE_LTO "Enable to add Link Time Optimization." ON)

# Project/Library Names
set(EXECUTABLE_NAME "hyphenation_console")

# CMAKE MODULES
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(ConfigSafeGuards)
include(AddGitSubmodule)
include(Docs)
include(Tools)

if(ENABLE_WARNINGS)
    include(Warnings)
endif()

add_cmake_format_target()
add_clang_format_target()

if(ENABLE_SANITIZE_ADDR
   OR ENABLE_SANITIZE_UNDEF
   OR ENABLE_SANITIZE_LEAK
   OR ENABLE_SANITIZE_THREAD)
    include(Sanitizer)
    add_sanitizer_flags()
endif()

if(ENABLE_TESTING AND ENABLE_COVERAGE)
    include(CodeCoverage)
    append_coverage_compiler_flags()
endif()

if(ENABLE_LTO)
    include(LTO)
endif()

# EXTERNAL LIBRARIES

if(USE_CPM)
    message(STATUS "Using CPM")
    include(CPM)
    cpmaddpackage("gh:nlohmann/json#v3.11.3")
    cpmaddpackage("gh:fmtlib/fmt#9.1.0")
    cpmaddpackage("gh:gabime/spdlog#v1.13.0")
    cpmaddpackage("gh:jarro2783/cxxopts#v3.1.1")
    #cpmaddpackage("gh:boostorg/boost#boost-1.86.0")
    # if(ENABLE_TESTING)
    #     cpmaddpackage("gh:catchorg/Catch2#v3.7.1")
    #     list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
    # endif()
    if(ENABLE_TESTING)
        cpmaddpackage("gh:google/googletest#v1.15.2")
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        # list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
    endif()
else()
    message(STATUS "Using FetchContent")
    FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.11.3
        GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(nlohmann_json)

    FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 10.0.0
        GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(fmt)

    FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog
        GIT_TAG v1.13.0
        GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(spdlog)

    FetchContent_Declare(
        cxxopts
        GIT_REPOSITORY https://github.com/jarro2783/cxxopts
        GIT_TAG v3.1.1
        GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(cxxopts)

    # FetchContent_Declare(
    #     Boost
    #     GIT_REPOSITORY https://github.com/boostorg/boost
    #     GIT_TAG boost-1.86.0 
    #     GIT_SHALLOW TRUE)
    # FetchContent_MakeAvailable(boostorg)
    # if(ENABLE_TESTING)
    # FetchContent_Declare(
    #     Catch2
    #     GIT_REPOSITORY https://github.com/catchorg/Catch2
    #     GIT_TAG v3.7.1
    #     GIT_SHALLOW TRUE)
    # FetchContent_MakeAvailable(Catch2)
    # list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
    # endif()
    if(ENABLE_TESTING)
        FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest
            GIT_TAG v1.15.2 
            GIT_SHALLOW TRUE)
        #set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googletest)
        #list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
    endif()
endif()

add_subdirectory(configured)
add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(app)
if(ENABLE_TESTING)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()

# INSTALL TARGETS

install(
    TARGETS ${EXECUTABLE_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

install(
    TARGETS "data_repository" core
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib)
