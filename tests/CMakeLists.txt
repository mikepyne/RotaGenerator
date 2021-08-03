add_executable(test_rg)

target_sources(test_rg
    PRIVATE
    main.cpp
    mock_volunteer.cpp
    mock_volunteer.h
    mock_event.cpp
    mock_event.h
    mock_rota.cpp
    mock_rota.h
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
    test_rotas.cpp
    test_rotas.h
    ${CMAKE_SOURCE_DIR}/src/rotadata.cpp
    ${CMAKE_SOURCE_DIR}/src/volunteer.cpp
    ${CMAKE_SOURCE_DIR}/src/rota.cpp
    ${CMAKE_SOURCE_DIR}/src/event.cpp
    ${CMAKE_SOURCE_DIR}/src/rgexception.cpp
    ${CMAKE_SOURCE_DIR}/src/mediator.cpp
)

target_include_directories(
    test_rg
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${spdlog_SOURCE_DIR}/include
    ${date_src_SOURCE_DIR}/include
)

target_link_libraries(
    test_rg
    PRIVATE
    Catch2::Catch2
    fmt
    date::date
)

target_compile_features(
    test_rg
    PRIVATE
    cxx_std_17
)

# Define HAS_UNCAUGHT_EXCEPTIONS so the date library compiles correctly.
target_compile_definitions(
    test_rg
    PRIVATE
    HAS_UNCAUGHT_EXCEPTIONS=1
)

set(ENABLE_COVERAGE ON CACHE INTERNAL "")

add_coverage(test_rg)

catch_discover_tests(test_rg)

coverage_evaluate(test_rg)
# The coverage report is generated using the following targets:
# * test_rg
# * test_rg-gcov
# * lcov-capture
# * lcov-genhtml
