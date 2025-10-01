#include "databasemodel.h"

#include <QBrush>
#include <QColor>
#include <QFont>

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
        if (_database && index.isValid())
        {
            if (index.column() < COLUMN_COUNT && index.row() < _database->size())
            {
                auto transaction = _database->transactionAt(index.row());
                if (role == Qt::DisplayRole)
                {
                    switch (index.column())
                    {
                    case Date:
                        return transaction.get()->dateTime().date();
                    case Amount:
                        return QString::number(transaction.get()->amount() * 0.01, 'f', 2);
                    case Category:
                        return transaction.get()->category();
                    case Description:
                        return transaction.get()->description();
                    default:
                        break;
                    }
                }
                else if (role == Qt::ForegroundRole)
                {
                    switch (transaction.get()->type())
                    {
                    case Transactions::Transaction::Income:
                        return QVariant(QBrush(Qt::green));
                    case Transactions::Transaction::Outcome:
                        return QVariant(QBrush(Qt::red));
                    default:
                        return QVariant(QBrush(Qt::black));
                    }
                }
                else if (role == Qt::CheckStateRole)
                {
                    switch (index.column())
                    {
                    case IsAnomaly:
                        if (transaction->anomalyStatus() == Transactions::Transaction::Anomalous)
                        {
                            if (transaction->anomalyStatusSource() == Transactions::Transaction::UserDefined)
                                return Qt::Checked;
                            else if (transaction->anomalyStatusSource() == Transactions::Transaction::Calculated)
                                return Qt::PartiallyChecked;
                        }
                        return Qt::Unchecked;
                    default:
                        break;
                    }
                }
            }
        }
        return QVariant();
    }

    bool DatabaseModel::setData(const QModelIndex &index, const QVariant &value, int role)
    {
        if (index.isValid() && index.column() == IsAnomaly)
        {
            auto transaction = _database->transactionAt(index.row());
            transaction->setAnomalyStatus(value.toBool() ? Transactions::Transaction::Anomalous : Transactions::Transaction::Normal);
            transaction->setAnomalyStatusSource(Transactions::Transaction::UserDefined);
            emit dataChanged(index, index);
            return true;
        }
        return QAbstractItemModel::setData(index, value, role);
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

    Qt::ItemFlags DatabaseModel::flags(const QModelIndex &index) const
    {
        Qt::ItemFlags res = QAbstractItemModel::flags(index);
        if (index.isValid() && index.column() == IsAnomaly)
            res |= Qt::ItemIsUserCheckable;
        return res;
    }

    QVariant DatabaseModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        {
            switch(section)
            {
            case Date:
                return "Date";
            case Amount:
                return "Amount";
            case Category:
                return "Category";
            case Description:
                return "Description";
            case IsAnomaly:
                return "Is anomaly";
            default:
                return QString();
            }
        }
        return QVariant();
    }

    void DatabaseModel::updateModel()
    {
        beginResetModel();
        endResetModel();
    }

    void DatabaseModel::setDatabase(Transactions::Database *newDatabase)
    {
        if (_database)
            QObject::disconnect(_database, nullptr, nullptr, nullptr);
        beginResetModel();
        _database = newDatabase;
        endResetModel();

        QObject::connect(_database, &Transactions::Database::changed, this, &DatabaseModel::updateModel);
    }

}
