# The main executable
add_executable(RotaGenerator)

target_sources(RotaGenerator
    PRIVATE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    rota.cpp
    rota.h
    rotadata.cpp
    rotadata.h
    volunteer.cpp
    volunteer.h
    event.cpp
    event.h
    rgexception.cpp
    rgexception.h
    mediator.cpp
    mediator.h
    volunteerdlg.cpp
    volunteerdlg.h
    volunteerdlg.ui
    eventsmodel.cpp
    eventsmodel.h
    rotasmodel.cpp
    rotasmodel.cpp
    volunteersmodel.cpp
    volunteersmodel.h
)

target_link_libraries(
    RotaGenerator
    PRIVATE
    Qt5::Widgets
    fmt
    date::date
    nlohmann_json::nlohmann_json
    spdlog::spdlog
)

# Define HAS_UNCAUGHT_EXCEPTIONS so the date library compiles correctly.
target_compile_definitions(
    RotaGenerator
    PRIVATE
    HAS_UNCAUGHT_EXCEPTIONS=1
)

# Documentation
find_package(Doxygen
    REQUIRED dot)

if(DOXYGEN_FOUND)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_MAN NO)
    set(DOXYGEN_OUTPUT_DIRECTORY source_docs)
    set(DOXYGEN_SOURCE_BROWSER YES)
    set(DOXYGEN_EXTRACT_PRIVATE NO)
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "README.md")
    set(DOXYGEN_EXCLUDE_PATTERNS
        */tests/*
        */*.py
        */${json_SOURCE_DIR}/*
        */${spdlog_SOURCE_DIR}/*
        */${date_SOURCE_DIR}/*
        */${trompeloeil_SOURCE_DIR}/*
        */${fmt_SOURCE_DIR}/*
        */${catch2_SOURCE_DIR}/*
    )

    doxygen_add_docs(
        doxygen
        ${CMAKE_CURRENT_SOURCE_DIR}
    )

else (DOXYGEN_FOUND)
  message("Doxygen needs to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
