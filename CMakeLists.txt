cmake_minimum_required(VERSION 3.16)

project(
    RotaGenerator
    DESCRIPTION "Generate rotas"
    LANGUAGES CXX
    VERSION 0.0.1
)

include(FetchContent)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include(json.cmake)
include(spdlog.cmake)
include(googletest.cmake)

add_subdirectory(src)
add_subdirectory(tests)
