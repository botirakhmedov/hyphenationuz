set(LIBRARY_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/transform_logic.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/word_extractor.cpp")
set(LIBRARY_HEADERS 
    "${CMAKE_CURRENT_SOURCE_DIR}/transform_logic.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/word_extractor.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/word_info_model.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library("transform_logic" STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories("transform_logic" INTERFACE ${LIBRARY_INCLUDES})
target_link_libraries(
    "transform_logic"
    PRIVATE "data_repository"
            nlohmann_json::nlohmann_json
            fmt::fmt
            spdlog::spdlog)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "transform_logic"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        "transform_logic"
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target("transform_logic")
endif()
