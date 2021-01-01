#include <filesystem>
#include <fstream>
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
//        std::filesystem::path p = "/home/pynem/volunteers.txt";
        std::fstream data("/home/mike/volunteers.txt", std::ios::in | std::ios::out | std::ios::app);
        if (data.good())
        {
            spdlog::debug("Opened file");
            vols.load(data);
            // auto details = av.volunteerDetails();
            // vols.add(details);
            // vols.save(data);
        }
    }
}
