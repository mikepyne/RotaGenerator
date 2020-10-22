enable_testing()

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.10.0
)

FetchContent_MakeAvailable(googletest)

set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST OFF CACHE BOOL "" FORCE)

include_directories(
    "${googletest_SOURCE_DIR}/googletest/include"
    "${googletest_SOURCE_DIR}/googlemock/include"
)

add_executable(test_rg)

target_sources(test_rg
    PRIVATE
    main.cpp
    test_volunteers.cpp
    test_volunteer.cpp
    test_event.cpp
    ${CMAKE_SOURCE_DIR}/src/volunteers.cpp
    ${CMAKE_SOURCE_DIR}/src/volunteer.cpp
    ${CMAKE_SOURCE_DIR}/src/event.cpp
)

target_include_directories(
    test_rg
    PUBLIC ${CMAKE_SOURCE_DIR}/src
#    ${spdlog_SOURCE_DIR}/include
)

target_link_libraries(
    test_rg
    gtest
)

target_compile_features(
    test_rg
    PRIVATE
    cxx_std_17
)

add_test(
    NAME test_rg
    COMMAND test_rg
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
