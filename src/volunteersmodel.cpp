#include "volunteersmodel.h"

VolunteersModel::VolunteersModel()
{

}

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
                return "Name";
            case 1:
                return "Home Phone";
            case 2:
                return "Mobile Phone";
            case 3:
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
    return 1;
}

int VolunteersModel::columnCount(
    const QModelIndex& parent
) const
{
    Q_UNUSED(parent);
    return 4;
}

QVariant VolunteersModel::data(
    const QModelIndex& index,
    int role
) const
{
    Q_UNUSED(index);
    Q_UNUSED(role);
    return QVariant("Something");
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
