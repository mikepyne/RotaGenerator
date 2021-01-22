#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMainWindow>

#include "rotadata.h"
#include "volunteer.h"
#include "volunteersmodel.h"
#include "event.h"
#include "eventsmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


/// \class MainWindow
/// \brief the main window for the application
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// \brief Constructor
    /// \param[in] parent parent
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void on_add_volunteer_clicked();

    void on_volunteers_toggled(
        bool checked
    );

    void on_events_toggled(
        bool checked
    );

private:
    Ui::MainWindow* ui; ///< The UI object
    std::shared_ptr<RotaData<Volunteer>> volunteers {std::make_shared<RotaData<Volunteer>>()};
    VolunteersModel volunteers_model {volunteers};
    std::shared_ptr<RotaData<Event>> events {std::make_shared<RotaData<Event>>()};
    EventsModel events_model {events};

    void loadVolunteers();

    void loadEvents();
};
#endif // MAINWINDOW_H
