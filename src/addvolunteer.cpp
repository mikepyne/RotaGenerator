#include <spdlog/spdlog.h>
#include <QPushButton>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

#include "addvolunteer.h"
#include "ui_addvolunteer.h"

AddVolunteer::AddVolunteer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddVolunteer)
{
    spdlog::debug("AddVolunteer");
    ui->setupUi(this);

    QRegularExpression rx("0\\d{2}[ -]\\d{4}[ -]\\d{4}|0\\d{3}[ -]\\d{3}[ -]\\d{4}|0\\d{4}[ -]\\d{5,6}");
    QRegularExpressionValidator rxv(rx, this);
}

AddVolunteer::~AddVolunteer()
{
    delete ui;
}

int AddVolunteer::exec()
{
    enableControls();
    return QDialog::exec();
}

void AddVolunteer::enableControls()
{
    spdlog::trace("enableControls");
    auto no_phone = ui->phone_home->text().isEmpty() && ui->phone_mobile->text().isEmpty();
    bool enable = !ui->first_name->text().isEmpty() &&
                  !ui->last_name->text().isEmpty() &&
                  !no_phone &&
                  !ui->email->text().isEmpty();

    auto button{ui->buttonBox->button(QDialogButtonBox::Ok)};
    button->setEnabled(enable);
}

void AddVolunteer::on_first_name_editingFinished()
{
    enableControls();
}

void AddVolunteer::on_last_name_editingFinished()
{
    enableControls();
}

void AddVolunteer::on_email_editingFinished()
{
    enableControls();
}

void AddVolunteer::on_phone_home_editingFinished()
{
    enableControls();
}

void AddVolunteer::on_phone_mobile_editingFinished()
{
    enableControls();
}
