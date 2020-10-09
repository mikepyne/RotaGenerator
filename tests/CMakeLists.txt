add_executable(test_rg)

target_sources(test_rg
    PRIVATE
    main.cpp
    test_volunteers.cpp
    test_volunteer.cpp
    ${CMAKE_SOURCE_DIR}/src/volunteers.cpp
    ${CMAKE_SOURCE_DIR}/src/volunteer.cpp
)

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