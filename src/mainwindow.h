#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui; ///< The UI object
};
#endif // MAINWINDOW_H
