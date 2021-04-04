#include <filesystem>
#include <fstream>
#include <exception>

#include <QSettings>
#include <QMessageBox>

#include <spdlog/spdlog.h>

#include "rgexception.h"

#include "volunteerdlg.h"
#include "volunteer.h"

#include "mainwindow.h"
#include "./ui_mainwindow.h"

using namespace rg;

MainWindow::MainWindow(
    QWidget *parent
)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    spdlog::debug("Creating MainWindow");
    ui->setupUi(this);

    ui->volunteers->click();

    loadVolunteers();

    ui->volunteersView->setModel(&volunteers_model);
    ui->volunteersView->setColumnHidden(0, true);
    for (int i {1}; i < volunteers_model.columnCount(); ++i)
    {
        ui->volunteersView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }
    ui->volunteersView->verticalHeader()->hide();
    ui->volunteersView->resizeColumnsToContents();

    loadEvents();

    ui->eventsView->setModel(&events_model);
    ui->eventsView->setColumnHidden(0, true);
    for (int i {1}; i < events_model.columnCount(); ++i)
    {
        ui->eventsView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }
    ui->eventsView->verticalHeader()->hide();
    ui->eventsView->resizeColumnsToContents();
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
    // auto details = av.volunteerDetails();
    // vols.add(details);
    // vols.save(data);
//    }
}

void MainWindow::on_volunteers_toggled(
    bool checked
)
{
    if (checked)
    {
        ui->stack->setCurrentIndex(0);
    }
}

void MainWindow::on_events_toggled(
    bool checked
)
{
    if (checked)
    {
        ui->stack->setCurrentIndex(1);
    }
}

void MainWindow::loadVolunteers()
{
    std::filesystem::path p = "/home/mike/Projects/RotaGenerator/data/volunteers.txt";
    std::fstream data(p, std::ios::in | std::ios::out | std::ios::app);

    if (data.good())
    {
        spdlog::debug("Opened file");
        try
        {
            volunteers->load(data);
        }
        catch (RGException& e)
        {
            spdlog::error("Error loading volunteers: {}", e.what());
            throw std::runtime_error("Error loading Volunteers data");
        }
    }
}

void MainWindow::loadEvents()
{
    std::filesystem::path p = "/home/mike/Projects/RotaGenerator/data/events.txt";
    std::fstream data(p, std::ios::in | std::ios::out | std::ios::app);

    if (data.good())
    {
        spdlog::debug("Opened file");
        try
        {
            events->load(data);
        }
        catch (RGException& e)
        {
            spdlog::error("Error loading events: {}", e.what());
            throw std::runtime_error("Error loading events data");
        }
    }
}
