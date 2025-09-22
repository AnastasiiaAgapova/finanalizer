#ifndef DATABASEMODEL_H
#define DATABASEMODEL_H

#include <QAbstractItemModel>

#include "transactions/database.h"
#include "transactions/database.h"

namespace Calculation
{
class Core;
}

namespace Widgets
{
class DatabaseModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    enum ColumnName
    {
        Date = 0,
        Amount,
        Category,
        Description,

        COLUMN_COUNT
    };

    explicit DatabaseModel(QObject *parent = nullptr);

    void setDatabase(Transactions::Database *newDatabase);

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &index) const;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void setCalculationCore(Calculation::Core *newCalculationCore);

protected slots:
    void updateModel();

private:
    Transactions::Database *_database;
    Calculation::Core *_calculationCore;
};
}

#endif // DATABASEMODEL_H
