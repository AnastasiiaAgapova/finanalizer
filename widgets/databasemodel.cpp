#include "databasemodel.h"

namespace Widgets
{

    DatabaseModel::DatabaseModel(QObject *parent)
        : QAbstractItemModel(parent)
        , _database(nullptr)
    {
    }

    int DatabaseModel::columnCount(const QModelIndex &parent) const
    {
        Q_UNUSED(parent);
        return COLUMN_COUNT;
    }

    QVariant DatabaseModel::data(const QModelIndex &index, int role) const
    {
        if (_database)
        {
            if (role == Qt::DisplayRole)
            {
                if (index.column() < COLUMN_COUNT && index.row() < _database->size())
                {
                    const Transactions::Transaction transaction = _database->transactionAt(index.row());
                    switch (index.column()) {
                    case Date:
                        return transaction.dateTime().date();
                    case Amount:
                        return transaction.amount() * 0.01;
                    case Category:
                        return transaction.category();
                    case Description:
                        return transaction.description();
                    default:
                        break;
                    }
                }
            }
        }
        return QVariant();
    }

    QModelIndex DatabaseModel::index(int row, int column, const QModelIndex &parent) const
    {
        if (nullptr == _database || parent.isValid())
        {
            return QModelIndex();
        }
        if (column >=0 && row >= 0 && column < COLUMN_COUNT && row < _database->size())
        {
            return createIndex(row, column, &_database->transactionAt(row));
        }
        return QModelIndex();
    }

    int DatabaseModel::rowCount(const QModelIndex &parent) const
    {
        if (_database)
            return _database->size();
        else
            return 0;
    }

    QModelIndex DatabaseModel::parent(const QModelIndex &index) const
    {
        return QModelIndex();
    }

    QVariant DatabaseModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        {
            if (section == Date)
                return "Date";
            else if (section == Amount)
                return "Amount";
            else if (section == Category)
                return "Category";
            else if (section == Description)
                return "Description";
        }
        return QVariant();
    }

    void DatabaseModel::setDatabase(Transactions::Database *newDatabase)
    {
        beginResetModel();
        _database = newDatabase;
        endResetModel();
    }

}
