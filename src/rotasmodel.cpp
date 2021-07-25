#include <spdlog/spdlog.h>

#include "rota.h"
#include "rotasmodel.h"

namespace rg
{
QVariant RotasModel::headerData(int             section,
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
            default:
                break;
        }
    }
    return QVariant();
}

int RotasModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return mediator->count(Mediator::CountTypes::Rotas);
}

int RotasModel::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return 3;
}

QVariant RotasModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        auto       id = index.row() + 1;
        const auto r  = mediator->getRota(id);
        switch (index.column())
        {
            case 0:
                return r.get_id();
            case 1:
                return QString::fromUtf8(r.get_label().c_str());
            case 2:
                return QString::fromUtf8(r.get_description().c_str());
        }
    }
    return QVariant();
}

}    // namespace rg
