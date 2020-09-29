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
    spdlog::trace("AddVolunteer");
    ui->setupUi(this);

    QRegularExpression phone_num("0\\d{2}[ -]\\d{4}[ -]\\d{4}|0\\d{3}[ -]\\d{3}[ -]\\d{4}|0\\d{4}[ -]\\d{5,6}");
    QValidator* pnv = new QRegularExpressionValidator(phone_num, this);
    ui->phone_home->setValidator(pnv);
    ui->phone_mobile->setValidator(pnv);

    QRegularExpression email("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b",
                             QRegularExpression::CaseInsensitiveOption);

    QValidator* ev = new QRegularExpressionValidator(email, this);
    ui->email->setValidator(ev);
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

    auto valid_phone {ui->phone_home->hasAcceptableInput() ||
                      ui->phone_mobile->hasAcceptableInput()};

    bool enable = !ui->first_name->text().isEmpty() &&
                  !ui->last_name->text().isEmpty() &&
                  valid_phone &&
                  ui->email->hasAcceptableInput();

    auto button{ui->buttonBox->button(QDialogButtonBox::Ok)};
    button->setEnabled(enable);
}

Details AddVolunteer::volunteerDetails()
{
    Details details {ui->first_name->text().toStdString(),
                     ui->last_name->text().toStdString(),
                     ui->phone_home->text().toStdString(),
                     ui->phone_mobile->text().toStdString(),
                     ui->email->text().toStdString()};

    return details;
}

void AddVolunteer::on_first_name_textChanged([[maybe_unused]] const QString &arg1)
{
    enableControls();
}

void AddVolunteer::on_last_name_textEdited([[maybe_unused]] const QString &arg1)
{
    enableControls();
}

void AddVolunteer::on_phone_home_textChanged([[maybe_unused]] const QString &arg1)
{
    enableControls();
}

void AddVolunteer::on_phone_mobile_textChanged([[maybe_unused]] const QString &arg1)
{
    enableControls();
}

void AddVolunteer::on_email_textChanged([[maybe_unused]] const QString &arg1)
{
    enableControls();
}
