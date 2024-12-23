set(LIBRARY_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/transform.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/action_point.cpp")
set(LIBRARY_HEADERS 
    "${CMAKE_CURRENT_SOURCE_DIR}/transform.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/core_error.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/result.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/action_point.h")
set(LIBRARY_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library(core STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(core INTERFACE ${LIBRARY_INCLUDES})
target_link_libraries(
    core
    PRIVATE data_repository
            commonlib
            data_repository
            nlohmann_json::nlohmann_json
            fmt::fmt
            spdlog::spdlog)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        core
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    target_enable_lto(
        TARGET
        core
        ENABLE
        ON)
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target(core)
endif()
