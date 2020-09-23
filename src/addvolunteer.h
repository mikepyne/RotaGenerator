#ifndef ADDVOLUNTEER_H
#define ADDVOLUNTEER_H

#include <QDialog>

#include <array>


namespace Ui {
class AddVolunteer;
}

using Details = std::array<std::string, 5>;

class AddVolunteer : public QDialog
{
    Q_OBJECT

public:
    explicit AddVolunteer(
        QWidget *parent = nullptr
    );

    ~AddVolunteer();

    int exec();

    Details volunteerDetails();

private slots:

    void on_first_name_textChanged(const QString &arg1);

    void on_last_name_textEdited(const QString &arg1);

    void on_phone_home_textChanged(const QString &arg1);

    void on_phone_mobile_textChanged(const QString &arg1);

    void on_email_textChanged(const QString &arg1);

private:
    Ui::AddVolunteer *ui;

    void enableControls();
};

#endif // ADDVOLUNTEER_H
