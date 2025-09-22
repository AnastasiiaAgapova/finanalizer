#include "databasemodel.h"

#include <QBrush>
#include <QColor>
#include <QFont>

#include "calculation/core.h"

namespace Widgets
{

    DatabaseModel::DatabaseModel(QObject *parent)
        : QAbstractItemModel(parent)
        , _database(nullptr)
        , _calculationCore(nullptr)
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
            if (index.column() < COLUMN_COUNT && index.row() < _database->size())
            {
                if (role == Qt::DisplayRole)
                {
                    auto transaction = _database->transactionAt(index.row());
                    switch (index.column()) {
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
                    const auto &transaction = _database->transactionAt(index.row());
                    switch (transaction.get()->type()) {
                    case Transactions::Transaction::INCOME:
                        return QVariant(QBrush(Qt::green));
                    case Transactions::Transaction::OUTCOME:
                        return QVariant(QBrush(Qt::red));
                    default:
                        return QVariant(QBrush(Qt::black));
                    }
                }
                else if (role == Qt::FontRole)
                {
                    if (!_calculationCore)
                        return QVariant();
                    const auto &transaction = _database->transactionAt(index.row());
                    if (_calculationCore && _calculationCore->isAnomaly(transaction))
                    {
                        QFont font;
                        font.setBold(true);
                        return font;
                    }
                    return QVariant();
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

    void DatabaseModel::updateModel()
    {
        beginResetModel();
        endResetModel();
    }

    void DatabaseModel::setCalculationCore(Calculation::Core *newCalculationCore)
    {
        if (_calculationCore)
            QObject::disconnect(_calculationCore, nullptr, nullptr, nullptr);
        _calculationCore = newCalculationCore;
        QObject::connect(_calculationCore, &Calculation::Core::analyzed, this, &DatabaseModel::updateModel);
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
