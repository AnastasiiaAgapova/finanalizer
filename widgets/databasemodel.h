#ifndef DATABASEMODEL_H
#define DATABASEMODEL_H

#include <QAbstractItemModel>

#include "transactions/database.h"
#include "transactions/database.h"

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
        IsAnomaly,

        COLUMN_COUNT
    };

    explicit DatabaseModel(QObject *parent = nullptr);

    void setDatabase(Transactions::Database *newDatabase);

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QModelIndex parent(const QModelIndex &index) const override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

protected slots:
    void updateModel();

private:
    Transactions::Database *_database;
};
}

#endif // DATABASEMODEL_H
