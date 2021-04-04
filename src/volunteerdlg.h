#ifndef VOLUNTEERDLG_H
#define VOLUNTEERDLG_H

#include <QDialog>

#include <array>

namespace Ui {
class VolunteerDlg;
}

namespace rg
{

using Details = std::array<std::string, 5>;

/// \class VolunteerDlg
/// \brief Dialog for adding or editing a volunteer's details
///
/// The dialog allows the user to enter or edit the details of a volunteer. The
/// details comprise first name, last name, home and/or mobile phone, and email.
/// The first name, last name and email are mandatory; one or both of the phone
/// numbers are required (i.e. either or both).
///
/// The phone numbers and email address are validated against a regular
/// expression.
class VolunteerDlg : public QDialog
{
    Q_OBJECT

public:
    /// \brief Constructor
    /// \param[in] parent owner object
    explicit VolunteerDlg(
        QWidget* parent = nullptr
    );

    ~VolunteerDlg();

    /// \brief Show the dialog
    int exec();

    /// \brief Get the new/updated volunteer details
    /// \return An array containing the details. Currently, this will be five
    ///         strings: first name, last name, home phone, mobile phone, email.
    Details volunteerDetails();

private slots:

    /// \name Slots
    /// \brief Text changed slots for the controls
    /// @{

    void on_first_name_textChanged(const QString &arg1);

    void on_last_name_textChanged(const QString &arg1);

    void on_phone_home_textChanged(const QString &arg1);

    void on_phone_mobile_textChanged(const QString &arg1);

    void on_email_textChanged(const QString &arg1);
    /// @}

private:
    Ui::VolunteerDlg *ui;   ///< The dialog object

    /// \brief Enable or disable controls
    ///
    /// Enable the OK button when the contents of the controls have passed
    /// validation
    void enableControls();
};

}   // namespace rg
#endif // VolunteerDlg_H
