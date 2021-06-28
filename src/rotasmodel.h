#ifndef ROTASMODEL_H
#define ROTASMODEL_H

#include <memory>

#include <QAbstractTableModel>

#include "mediator.h"

namespace rg
{
/// \class RotasModel
/// \brief Model for displaying Rotas on a view
///
/// Derived from a Qt <a href="https://doc.qt.io/qt-5/qabstracttablemodel.html">
/// QAbstractTableModel</a>.
class RotasModel : public QAbstractTableModel
{
    Q_OBJECT

    public:
    RotasModel() = delete;

    /// \brief Construct a model
    /// \param m #rg::Mediator
    RotasModel(std::shared_ptr<rg::Mediator> m) : mediator(m) {};

    /// \brief Get the header for the view
    QVariant headerData(
        int             section,
        Qt::Orientation orientation,
        int             role = Qt::DisplayRole) const override;

    /// \brief Number of rows in the model
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    /// \brief Number of columns in the model
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    /// \brief Get the data for a cell
    QVariant
        data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    private:
    std::shared_ptr<rg::Mediator> mediator;
};

}    // namespace rg
#endif    // ROTASMODEL_H
