#include "databesasortfilterproxymodel.h"

#include "databasemodel.h"

namespace Widgets
{
DatabesaSortFilterProxyModel::DatabesaSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{

}

void DatabesaSortFilterProxyModel::setFilter(const std::shared_ptr<Transactions::Filter> &newFilter)
{
    beginFilterChange();
    _filter = newFilter;
    invalidateRowsFilter();
}

bool DatabesaSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (sourceParent.isValid())
        return true;
    if (!_filter.get())
        return true;
    else
    {
        auto transaction = static_cast<std::shared_ptr<Transactions::Transaction>*>(sourceModel()->index(sourceRow, 0, sourceParent).internalPointer());
        return _filter->isMatch(*transaction);
    }
}

bool DatabesaSortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);



    switch (left.column()) {
    case DatabaseModel::Date:
        return leftData.toDateTime() < rightData.toDateTime();
    case DatabaseModel::Amount:
        return  leftData.toDouble() < rightData.toDouble();
    case DatabaseModel::Category:
    case DatabaseModel::Description:
        return leftData.toString() < rightData.toString();
    case DatabaseModel::IsAnomaly:
    {
        QVariant leftCheckedData = left.data(Qt::CheckStateRole);
        QVariant rightCheckedData = right.data(Qt::CheckStateRole);
        return leftCheckedData.toInt() < rightCheckedData.toInt();
    }
    default:
        return true;
    }
}
}
