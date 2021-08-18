#include <filesystem>
#include <fstream>
#include <exception>

#include <QSettings>
#include <QMessageBox>
#include <QStandardPaths>

#include <spdlog/spdlog.h>

#include "rgexception.h"

#include "volunteerdlg.h"
#include "volunteer.h"

#include "mainwindow.h"
#include "./ui_mainwindow.h"

using namespace rg;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    spdlog::debug("Creating MainWindow");
    ui->setupUi(this);

    ui->volunteers->click();

    QString d = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    std::filesystem::path data_path {d.toStdString()};
    try
    {
        mediator->loadData(data_path);

        ui->volunteersView->setModel(&volunteers_model);
        ui->volunteersView->setColumnHidden(0, true);
        for (int i {1}; i < volunteers_model.columnCount(); ++i)
        {
            ui->volunteersView->horizontalHeader()->setSectionResizeMode(
                i,
                QHeaderView::Stretch);
        }
        ui->volunteersView->verticalHeader()->hide();
        ui->volunteersView->resizeColumnsToContents();

        ui->eventsView->setModel(&events_model);
        ui->eventsView->setColumnHidden(0, true);
        for (int i {1}; i < events_model.columnCount(); ++i)
        {
            ui->eventsView->horizontalHeader()->setSectionResizeMode(
                i,
                QHeaderView::Stretch);
        }
        ui->eventsView->verticalHeader()->hide();
        ui->eventsView->resizeColumnsToContents();

        ui->rotasView->setModel(&rotas_model);
        ui->rotasView->setColumnHidden(0, true);
        for (int i {1}; i < rotas_model.columnCount(); ++i)
        {
            ui->rotasView->horizontalHeader()->setSectionResizeMode(
                i,
                QHeaderView::Stretch);
        }
    }
    catch (RGException& e)
    {
        QMessageBox msg;
        msg.setText(QString::fromStdString(e.what()));
        msg.exec();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_volunteer_clicked()
{
    spdlog::debug("In the click");
    volunteers_model.insertRows(volunteers_model.rowCount() + 1, 1, QModelIndex());
    //    VolunteerDlg av;
    //    if (av.exec() == QDialog::Accepted)
    //    {
    // auto details = av.volunteerDetails();
    // vols.add(details);
    // vols.save(data);
    //    }
}

void MainWindow::on_volunteers_toggled(bool checked)
{
    if (checked)
    {
        ui->stack->setCurrentIndex(0);
    }
}

void MainWindow::on_events_toggled(bool checked)
{
    if (checked)
    {
        ui->stack->setCurrentIndex(1);
    }
}

void MainWindow::on_rotas_toggled(bool checked)
{
    if (checked)
    {
        ui->stack->setCurrentIndex(2);
    }
}
