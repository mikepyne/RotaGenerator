#ifndef ADDVOLUNTEER_H
#define ADDVOLUNTEER_H

#include <QDialog>

namespace Ui {
class AddVolunteer;
}

class AddVolunteer : public QDialog
{
    Q_OBJECT

public:
    explicit AddVolunteer(
        QWidget *parent = nullptr
    );

    ~AddVolunteer();

    int exec();

private slots:
    void on_first_name_editingFinished();

    void on_last_name_editingFinished();

    void on_email_editingFinished();

    void on_phone_home_editingFinished();

    void on_phone_mobile_editingFinished();

private:
    Ui::AddVolunteer *ui;

    void enableControls();
};

#endif // ADDVOLUNTEER_H
