#include "eventsmodel.h"

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
    return events->count();
}

int EventsModel::columnCount(
    const QModelIndex& parent
) const
{
    Q_UNUSED(parent);
    return 4;
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
        const auto e = events->at(id);
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
            default:
                break;
        }
    }
    return QVariant();
}
