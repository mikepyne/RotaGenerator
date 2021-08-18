#include <spdlog/spdlog.h>

#include "volunteer.h"
#include "volunteersmodel.h"

namespace rg
{
QVariant VolunteersModel::headerData(int             section,
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

int VolunteersModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return mediator->count(Mediator::CountTypes::Volunteers);
}

int VolunteersModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return 5;
}

QVariant VolunteersModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        // Calculating the ID from the row index might be a bad idea.
        auto       id = index.row() + 1;
        const auto v  = mediator->getVolunteer(id);
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

bool VolunteersModel::setData(const QModelIndex& index,
                              const QVariant&    value,
                              int                role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        auto id  = index.row() + 1;
        auto vol = mediator->getVolunteer(id);
        auto val = value.toString().toStdString();

        switch (index.column())
        {
            case 1:
                vol.set_name(val);
                break;
            case 2:
                vol.set_phone_home(val);
                break;
            case 3:
                vol.set_phone_mobile(val);
                break;
            case 4:
                vol.set_email(val);
                break;
            default:
                break;
        }
        mediator->updateVolunteer(vol);
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
        return true;
    }
    return false;
}

Qt::ItemFlags VolunteersModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
    {
        return Qt::ItemIsEnabled;
    }

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool VolunteersModel::insertRows(int row, int count, const QModelIndex& parent)
{
    beginInsertRows(parent, row, row + count - 1);
    endInsertRows();
    return true;
}

}    // namespace rg
