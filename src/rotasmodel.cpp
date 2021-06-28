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

    // FIXME: Implement me!
    return QVariant();
}

}    // namespace rg
