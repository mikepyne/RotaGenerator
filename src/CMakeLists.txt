add_executable(RotaGenerator
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    volunteerdlg.cpp
    volunteerdlg.h
    volunteerdlg.ui
    volunteer.cpp
    volunteer.h
    volunteers.cpp
    volunteers.h
)

target_link_libraries(RotaGenerator PRIVATE Qt5::Widgets)

find_package(Doxygen
    REQUIRED dot)

if(DOXYGEN_FOUND)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_MAN NO)
    set(DOXYGEN_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/source_docs)
    set(DOXYGEN_SOURCE_BROWSER YES)
    set(DOXYGEN_EXTRACT_PRIVATE NO)
    set(DOXYGEN_EXCLUDE_PATTERNS
        */tests/*
        */*.py
    )

    doxygen_add_docs(
        doxygen
        ${PROJECT_SOURCE_DIR}
    )

else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
