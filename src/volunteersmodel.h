#ifndef VOLUNTEERSMODEL_H
#define VOLUNTEERSMODEL_H

#include <QAbstractTableModel>

class VolunteersModel : public QAbstractTableModel
{
public:
    VolunteersModel();

    QVariant headerData(
        int section,
        Qt::Orientation orientation,
        int role = Qt::DisplayRole
    ) const override;

    int rowCount(
        const QModelIndex& parent = QModelIndex()
    ) const override;

    int columnCount(
        const QModelIndex& parent = QModelIndex()
    ) const override;

    QVariant data(
        const QModelIndex& index,
        int role = Qt::DisplayRole
    ) const;

//    bool setData(
//        const QModelIndex& index,
//        const QVariant& value,
//        int role = Qt::EditRole
//    ) override;

//    Qt::ItemFlags flags(
//        const QModelIndex& index
//    ) const override;


};

#endif // VOLUNTEERSMODEL_H
