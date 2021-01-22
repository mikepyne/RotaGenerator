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
                return "Label";
            case 1:
                return "Description";
            case 2:
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
    return 3;
}

QVariant EventsModel::data(
    const QModelIndex& index,
    int role
) const
{
    Q_UNUSED(index);
    if (role == Qt::DisplayRole)
    {
        // Calculating the ID from the row index might be a bad idea.
        const std::string id = std::to_string(index.row() + 1);
        const auto e = events->at(id);
        switch (index.column())
        {
            case 0:
            {
                return QString::fromUtf8(e.get_label().c_str());
            }
            case 1:
                return QString::fromUtf8(e.get_description().c_str());
            case 2:
                return e.get_vols_needed();
            default:
                break;
        }
    }
    return QVariant();
}
