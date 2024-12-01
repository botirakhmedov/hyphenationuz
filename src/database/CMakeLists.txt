set(LIBRARY_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/data_repository.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sqlite3.c")
set(LIBRARY_HEADERS 
    "${CMAKE_CURRENT_SOURCE_DIR}/interface.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/data_repository.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/sqlite3.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library(data_repository STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(data_repository SYSTEM INTERFACE ${LIBRARY_INCLUDES})
target_link_libraries(
    "data_repository"
    PRIVATE commonlib 
            nlohmann_json::nlohmann_json
            fmt::fmt
            spdlog::spdlog)
#target_compile_options("data_repository" PRIVATE "-w")
# if(${ENABLE_WARNINGS})
#     target_set_warnings(
#         TARGET
#         "data_repository"
#         ENABLE
#         ${ENABLE_WARNINGS}
#         AS_ERRORS
#         ${ENABLE_WARNINGS_AS_ERRORS})
# endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        data_repository
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target(data_repository)
endif()
