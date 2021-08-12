#include "event.h"
#include "eventsmodel.h"

namespace rg
{
QVariant EventsModel::headerData(int             section,
                                 Qt::Orientation orientation,
                                 int             role) const
{
    Q_UNUSED(orientation);

    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
            case 0:
                return "ID";
            case 1:
                return "Label";
            case 2:
                return "Description";
            case 3:
                return "Number of Volunteers";
            case 4:
                return "Day";
            default:
                break;
        }
    }
    return QVariant();
}

int EventsModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return mediator->count(Mediator::CountTypes::Events);
}

int EventsModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return 5;
}

QVariant EventsModel::data(const QModelIndex& index, int role) const
{
    Q_UNUSED(index);
    if (role == Qt::DisplayRole)
    {
        auto       id = index.row() + 1;
        const auto e  = mediator->getEvent(id);
        switch (index.column())
        {
            case 0:
                return e.get_id();
            case 1:
                return QString::fromUtf8(e.get_label().c_str());
            case 2:
                return QString::fromUtf8(e.get_description().c_str());
            case 3:
                return e.get_vols_needed();
            case 4:
            {
                std::string day {Event::day_to_string(e.get_day())};
                return QString::fromUtf8(day.c_str());
            }
            default:
                break;
        }
    }
    return QVariant();
}

bool EventsModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        auto id    = index.row() + 1;
        auto event = mediator->getEvent(id);
        auto val   = value.toString().toStdString();

        switch (index.column())
        {
            case 1:
                event.set_label(val);
                break;
            case 2:
                event.set_description(val);
                break;
            case 3:
                event.set_vols_needed(value.toInt());
                break;
            case 4:
                event.set_day(value.toInt());
                break;
            default:
                break;
        }
        // TODO: Add updateEvent to the mediator.
        //        mediator->updateEvent(event);
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
        return true;
    }
    return false;
}

Qt::ItemFlags EventsModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
    {
        return Qt::ItemIsEnabled;
    }

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

}    // namespace rg
