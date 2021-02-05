#include <spdlog/spdlog.h>

#include "volunteersmodel.h"


QVariant VolunteersModel::headerData(
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
                return"ID";
            case 1:
                return "Name";
            case 2:
                return "Home Phone";
            case 3:
                return "Mobile Phone";
            case 4:
                return "Email";
            default:
                break;
        }
    }
    return QVariant();
}

int VolunteersModel::rowCount(
    const QModelIndex& parent
) const
{
    Q_UNUSED(parent);
    return volunteers->count();
}

int VolunteersModel::columnCount(
    const QModelIndex& parent
) const
{
    Q_UNUSED(parent);
    return 5;
}

QVariant VolunteersModel::data(
    const QModelIndex& index,
    int role
) const
{
    if (role == Qt::DisplayRole)
    {
        // Calculating the ID from the row index might be a bad idea.
        auto id = index.row() + 1;
        const auto v = volunteers->at(id);
        switch (index.column())
        {
            case 0:
                return v.get_id();
            case 1:
                return QString::fromUtf8(v.get_name().c_str());
            case 2:
                return QString::fromUtf8(v.get_phone_home().c_str());
            case 3:
                return QString::fromUtf8(v.get_phone_mobile().c_str());
            case 4:
                return QString::fromUtf8(v.get_email().c_str());
            default:
                break;
        }
    }
    return QVariant();
}

//bool VolunteersModel::setData(
//    const QModelIndex& index,
//    const QVariant& value,
//    int role
//)
//{
//    Q_UNUSED(index);
//    Q_UNUSED(value);
//    Q_UNUSED(role);
//    return false;
//}

//Qt::ItemFlags VolunteersModel::flags(
//    const QModelIndex& index
//) const
//{
//    Q_UNUSED(index);
//    return Qt::ItemFlag::ItemIsSelectable;
//}
