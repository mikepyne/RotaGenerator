add_executable(RotaGenerator
main.cpp
mainwindow.cpp
mainwindow.h
mainwindow.ui
addvolunteer.cpp
addvolunteer.h
addvolunteer.ui
)

target_link_libraries(RotaGenerator PRIVATE Qt5::Widgets)
