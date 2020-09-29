cmake_minimum_required(VERSION 3.16)

project(
    RotaGenerator
    DESCRIPTION "Generate rotas"
    LANGUAGES CXX
    VERSION 0.0.1
)

include(FetchContent)

enable_testing()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.7.0
)

FetchContent_Declare(
    json
    GIT_REPOSITORY  https://github.com/nlohmann/json.git
    GIT_TAG         v3.9.1
)

if (NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

FetchContent_Declare(
    catch2
    GIT_REPOSITORY  https://github.com/catchorg/Catch2.git
    GIT_TAG         v2.13.0
)

FetchContent_MakeAvailable(spdlog json catch2)

set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")

set(SPDLOG_BUILD_EXAMPLE OFF CACHE INTERNAL "")
set(SPDLOG_BUILD_TESTS OFF CACHE INTERNAL "")
set(SPDLOG_INSTALL OFF CACHE INTERNAL "")

set(CATCH_BUILD_TESTING OFF)
set(CATCH_BUILD_EXAMPLES OFF)
set(CATCH_INSTALL_DOCS OFF)
set(CATCH_INSTALL_HELPERS OFF)

include_directories(
    "${json_SOURCE_DIR}/include"
    "${spdlog_SOURCE_DIR}/include"
    "${catch2_SOURCE_DIR}/single_include"
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)
