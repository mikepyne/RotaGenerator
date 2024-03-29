add_executable(RotaGenerator)

target_sources(RotaGenerator
    PRIVATE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    volunteerdlg.cpp
    volunteerdlg.h
    volunteerdlg.ui
    volunteersmodel.cpp
    volunteersmodel.h
    eventsmodel.cpp
    eventsmodel.h
    rotasmodel.cpp
    rotasmodel.h
    rotadata.cpp
    volunteer.cpp
    rota.cpp
    event.cpp
    rgexception.cpp
    mediator.cpp
)

target_link_libraries(
    RotaGenerator
    PRIVATE
    Qt5::Widgets
    fmt
    date::date
)

# Define HAS_UNCAUGHT_EXCEPTIONS so the date library compiles correctly.
target_compile_definitions(
    RotaGenerator
    PRIVATE
    HAS_UNCAUGHT_EXCEPTIONS=1
)

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
        */${googletest_SOURCE_DIR}/*
    )

    doxygen_add_docs(
        doxygen
        ${PROJECT_SOURCE_DIR}
    )

else (DOXYGEN_FOUND)
  message("Doxygen needs to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
