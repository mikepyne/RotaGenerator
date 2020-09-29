set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/volunteers.cpp
    ${CMAKE_SOURCE_DIR}/src/volunteer.cpp
)

set(TEST_SOURCES
    main.cpp
    test_volunteers.cpp
)

add_executable(test_rg ${SOURCES} ${TEST_SOURCES})

target_include_directories(
    test_rg
    PUBLIC ${CMAKE_SOURCE_DIR}/src
    ${spdlog_SOURCE_DIR}/include
    ${json_SOURCE_DIR}/include
)

target_compile_features(test_rg PRIVATE cxx_std_17)

add_test(
    NAME test_rg
    COMMAND test_rg
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
