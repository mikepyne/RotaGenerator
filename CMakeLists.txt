cmake_minimum_required(VERSION 3.16)

project(RotaGenerator LANGUAGES CXX VERSION 0.0.1)

include(FetchContent)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
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

include_directories(
    "${json_SOURCE_DIR}/include"
    "${spdlog_SOURCE_DIR}/include"
    "${catch2_SOURCE_DIR}/single_include"
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_subdirectory(src)
