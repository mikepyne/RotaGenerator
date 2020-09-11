#include <spdlog/spdlog.h>

#include "addvolunteer.h"

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    spdlog::debug("Creating MainWindow");
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    spdlog::debug("In the click");
    AddVolunteer av;
    av.exec();
}
