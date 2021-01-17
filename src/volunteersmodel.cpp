#include <filesystem>
#include <fstream>
#include <exception>

#include <spdlog/spdlog.h>

#include "volunteersmodel.h"

VolunteersModel::VolunteersModel()
{
    std::filesystem::path p = "/home/mike/Projects/RotaGenerator/data/volunteers.txt";
    std::fstream data(p, std::ios::in | std::ios::out | std::ios::app);

    if (data.good())
    {
        spdlog::debug("Opened file");
        try
        {
            volunteers.load(data);
        }
        catch (json::out_of_range e)
        {
            spdlog::error("Error loading volunteers: {}", e.what());
            throw std::runtime_error("Error loading Volunteers data");
        }
    }
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
    return volunteers.count();
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
    if (role == Qt::DisplayRole)
    {
        // Calculating the ID from the row index might be a bad idea.
        const std::string id = std::to_string(index.row() + 1);
        const auto v = volunteers.at(id);
        switch (index.column())
        {
            case 0:
            {
                auto n = v.get_first_name() + " " + v.get_last_name();
                return QString::fromUtf8(n.c_str());
            }
            case 1:
                return QString::fromUtf8(v.get_phone_home().c_str());
            case 2:
                return QString::fromUtf8(v.get_phone_mobile().c_str());
            case 3:
                return QString::fromUtf8(v.get_email().c_str());
                break;
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
