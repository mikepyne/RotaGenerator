#include <spdlog/spdlog.h>
#include <QPushButton>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

#include "volunteerdlg.h"
#include "ui_volunteerdlg.h"

namespace rg
{

VolunteerDlg::VolunteerDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VolunteerDlg)
{
    spdlog::trace("VolunteerDlg");
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

VolunteerDlg::~VolunteerDlg()
{
    delete ui;
}

int VolunteerDlg::exec()
{
    enableControls();
    return QDialog::exec();
}

void VolunteerDlg::enableControls()
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

Details VolunteerDlg::volunteerDetails()
{
    Details details {ui->first_name->text().toStdString(),
                     ui->last_name->text().toStdString(),
                     ui->phone_home->text().toStdString(),
                     ui->phone_mobile->text().toStdString(),
                     ui->email->text().toStdString()};

    return details;
}

void VolunteerDlg::on_first_name_textChanged([[maybe_unused]] const QString &arg1)
{
    enableControls();
}

void VolunteerDlg::on_last_name_textChanged([[maybe_unused]] const QString &arg1)
{
    enableControls();
}

void VolunteerDlg::on_phone_home_textChanged([[maybe_unused]] const QString &arg1)
{
    enableControls();
}

void VolunteerDlg::on_phone_mobile_textChanged([[maybe_unused]] const QString &arg1)
{
    enableControls();
}

void VolunteerDlg::on_email_textChanged([[maybe_unused]] const QString &arg1)
{
    enableControls();
}

}   // namespace rg
