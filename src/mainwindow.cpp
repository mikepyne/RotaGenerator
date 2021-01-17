#include <spdlog/spdlog.h>

#include <QSettings>
#include <QMessageBox>

#include "volunteerdlg.h"
#include "volunteer.h"

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    spdlog::debug("Creating MainWindow");
    ui->setupUi(this);

    ui->volunteers->click();

    ui->volunteersView->setModel(&volunteers);
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
