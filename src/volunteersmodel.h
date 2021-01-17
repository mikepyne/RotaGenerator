#ifndef VOLUNTEERSMODEL_H
#define VOLUNTEERSMODEL_H

#include <QAbstractTableModel>

#include "rotadata.h"
#include "volunteer.h"

/// \class VolunteersModel
/// \brief Model for displaying Volunteers on a view.
///
/// Derived from a Qt <a href="https://doc.qt.io/qt-5/qabstracttablemodel.html">
/// QAbstractTableModel</a>.
class VolunteersModel : public QAbstractTableModel
{
public:
    VolunteersModel();

    /// \brief Get the header for the view
    QVariant headerData(
        int section,
        Qt::Orientation orientation,
        int role = Qt::DisplayRole
    ) const override;

    /// \brief Number of rows in the model
    int rowCount(
        const QModelIndex& parent = QModelIndex()
    ) const override;

    /// \brief Number of columns in the model
    int columnCount(
        const QModelIndex& parent = QModelIndex()
    ) const override;

    /// \brief Get the data for a cell
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

private:
    RotaData<Volunteer> volunteers;
};

#endif // VOLUNTEERSMODEL_H
