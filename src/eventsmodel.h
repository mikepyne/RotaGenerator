#ifndef EVENTSMODEL_H
#define EVENTSMODEL_H

#include <memory>

#include <QAbstractTableModel>

#include "rotadata.h"
#include "event.h"


class EventsModel : public QAbstractTableModel
{
public:
    EventsModel() = delete;

    EventsModel(
        std::shared_ptr<RotaData<Event>> e
    ) : events(e) {};

    QVariant headerData(
        int section,
        Qt::Orientation orientation,
        int role = Qt::DisplayRole
    ) const override;

    int rowCount(
        const QModelIndex& parent = QModelIndex()
    ) const override;

    int columnCount(
        const QModelIndex& parent = QModelIndex()
    ) const override;

    QVariant data(
        const QModelIndex& index,
        int role = Qt::DisplayRole
    ) const override;

private:
    std::shared_ptr<RotaData<Event>> events;
};

#endif // EVENTSMODEL_H
