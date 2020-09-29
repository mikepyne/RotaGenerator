#include <spdlog/spdlog.h>

#include "volunteerdlg.h"
#include "volunteers.h"
#include "volunteer.h"

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


void MainWindow::on_add_volunteer_clicked()
{
    spdlog::debug("In the click");
    VolunteerDlg av;
    if (av.exec() == QDialog::Accepted)
    {
        Volunteers vols;
        vols.load("~/Projects/RotaGenerator");
        // TODO: construct volunteer from the dialog
        auto details = av.volunteerDetails();
        vols.add(details);
    }
}
