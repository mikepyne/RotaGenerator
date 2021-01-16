#include <filesystem>
#include <fstream>
#include <spdlog/spdlog.h>

#include <QSettings>
#include <QMessageBox>

#include "volunteerdlg.h"
#include "volunteers.h"
#include "volunteer.h"

#include "volunteersmodel.h"

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    spdlog::debug("Creating MainWindow");
    ui->setupUi(this);

    VolunteersModel* vmodel = new VolunteersModel();
    ui->volunteersView->setModel(vmodel);
    ui->volunteersView->horizontalHeader()->setStretchLastSection(true);
    ui->volunteersView->verticalHeader()->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_volunteer_clicked()
{
    spdlog::debug("In the click");
//    VolunteerDlg av;
//    if (av.exec() == QDialog::Accepted)
//    {
        Volunteers vols;
        std::filesystem::path p = "/home/mike/Projects/RotaGenerator/data/volunteers.txt";
        std::fstream data("/home/mike/Projects/RotaGenerator/data/volunteers.txt", std::ios::in | std::ios::out | std::ios::app);
        if (data.good())
        {
            spdlog::debug("Opened file");
            try {
                vols.load(data);
            }
            catch (json::out_of_range e)
            {
                spdlog::error("Error loading volunteers: {}", e.what());
                QMessageBox m;
                m.setText("Unable to load the volunteers");
                m.setInformativeText(e.what());
                m.exec();
            }
            // auto details = av.volunteerDetails();
            // vols.add(details);
            // vols.save(data);
        }
//    }
}
