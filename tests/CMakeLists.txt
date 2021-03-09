
add_executable(test_rg)

target_sources(test_rg
    PRIVATE
    main.cpp
    mock_volunteer.cpp
    mock_volunteer.h
    mock_event.cpp
    mock_event.h
    test_volunteers.cpp
    test_volunteers.h
    test_volunteer.cpp
    test_volunteer.h
    test_event.cpp
    test_event.h
    test_events.cpp
    test_events.h
    test_exceptions.cpp
    test_rota.cpp
    test_rota.h
    ${CMAKE_SOURCE_DIR}/src/rotadata.cpp
    ${CMAKE_SOURCE_DIR}/src/volunteer.cpp
    ${CMAKE_SOURCE_DIR}/src/event.cpp
    ${CMAKE_SOURCE_DIR}/src/rgexception.cpp
    ${CMAKE_SOURCE_DIR}/src/rota.cpp
)

target_include_directories(
    test_rg
    PUBLIC ${CMAKE_SOURCE_DIR}/src
    ${spdlog_SOURCE_DIR}/include
)

target_link_libraries(
    test_rg
    Catch2::Catch2
    fmt
)

target_compile_features(
    test_rg
    PRIVATE
    cxx_std_17
)

catch_discover_tests(test_rg)
