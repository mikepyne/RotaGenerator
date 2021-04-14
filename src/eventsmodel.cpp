#include "event.h"
#include "eventsmodel.h"

namespace rg
{

QVariant EventsModel::headerData(
    int section,
    Qt::Orientation orientation,
    int role
) const
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

int EventsModel::rowCount(
    const QModelIndex& parent
) const
{
    Q_UNUSED(parent)
    return mediator->count(Mediator::CountTypes::Events);
}

int EventsModel::columnCount(
    const QModelIndex& parent
) const
{
    Q_UNUSED(parent);
    return 5;
}

QVariant EventsModel::data(
    const QModelIndex& index,
    int role
) const
{
    Q_UNUSED(index);
    if (role == Qt::DisplayRole)
    {
        auto id = index.row() + 1;
        const auto e = mediator->getEvent(id);
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

}   // namespace rg
