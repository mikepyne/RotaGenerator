#ifndef EVENTSMODEL_H
#define EVENTSMODEL_H

#include <memory>

#include <QAbstractTableModel>

#include "rotadata.h"
#include "event.h"

/// \class EventsModel
/// \brief Model for displaying Events on a view.
///
/// Derived from a Qt <a href="https://doc.qt.io/qt-5/qabstracttablemodel.html">
/// QAbstractTableModel</a>.
class EventsModel : public QAbstractTableModel
{
public:
    EventsModel() = delete;

    /// \brief Construct the model
    /// \param e the list of events
    EventsModel(
        std::shared_ptr<RotaData<Event>> e
    ) : events(e) {};

    /// \brief Get the header for the view
    QVariant headerData(
        int section,
        Qt::Orientation orientation,
        int role = Qt::DisplayRole
    ) const override;

    /// \brief Number of rows in the model
    int rowCount(
        const QModelIndex& parent = QModelIndex()
    ) const override;

    /// \brief Number of columns in the model
    int columnCount(
        const QModelIndex& parent = QModelIndex()
    ) const override;

    /// \brief Get the data for a cell
    QVariant data(
        const QModelIndex& index,
        int role = Qt::DisplayRole
    ) const override;

private:
    std::shared_ptr<RotaData<Event>> events;    ///< Events
};

#endif // EVENTSMODEL_H
